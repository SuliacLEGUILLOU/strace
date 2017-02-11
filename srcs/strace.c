
#include "../hdrs/strace.h"
#include "../hdrs/signal.h"

static t_trap	st_trapPid(pid_t pid, int* status)
{
	int		signal;

	while (1) {
		(void)ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		if (waitpid(pid, status, 0) < 0)
			fatal(ERR_WAIT);

		if (WIFSTOPPED(*status)) {
			signal = WSTOPSIG(*status);
			if (signal & SYSCALL_MASK)
				return (syscall_);
			else
				return (signal_);
		}
		if (WIFEXITED(*status) || WIFSIGNALED(*status))
			return (exit_);
	}
}

static int	st_trap_signal(pid_t pid, int* status)
{
	return printf("Signal catch\n");
}

static int	st_trap_syscall(pid_t pid, int* status)
{
	long						syscall, ret;
	const t_syscall_info*		info;
	t_syscall_arg				args[ARGC_MAX];
	t_trap						trap;
	void*						retVal;

	syscall = get_usr(pid, ORIG_RAX);
	get_arg(pid, syscall, args);
	//printf("Print first trap\n");

	trap = st_trapPid(pid, status);
	if (trap == exit_){
		printf("Unknow return\n");
		return (1);
	}
	else if (trap == syscall_) {
		ret = get_usr(pid, RAX);
		info = get_syscall_info(syscall);
		retVal = (info) ? get_val(pid, info->ret_type, ret) : NULL;
		print_syscall(info, args, retVal);
	}
	else if (trap == signal_)
		return (st_trap_signal(pid, status));
	return (0);
}

static int	st_trace(pid_t pid)
{
	t_trap	trap;
	int		status;
	int		cont;

	if (ptrace(PTRACE_SEIZE, pid, NULL, OPTION_PTRACE))
		fatal(ERR_TRAC);
	do {
		cont = 0;
		trap = st_trapPid(pid, &status);
		if (trap == syscall_)
			cont = st_trap_syscall(pid, &status);
		else if (trap == signal_)
			cont = st_trap_signal(pid, &status);
	} while (trap != exit_ && !cont);
	return (0);
}

int		strace(const char** cmd, const char** env)
{
	char*	bin = getpath(cmd[0], env);
	int		ret = 0;
	pid_t	pid;

	if (!bin)
		fatal(ERR_EXEC);
	pid = fork();
	if (pid == -1)
		fatal(ERR_FORK);
	else if (pid == 0){
		kill(getpid(), SIGSTOP);
		execve(bin, (char**)cmd, (char**)env);
		fatal(ERR_EXEC);
	}
	else {
		if (waitpid(pid, NULL, WUNTRACED) == -1)
			fatal(ERR_WAIT);
		ret = st_trace(pid);
	}
	return (ret);
}

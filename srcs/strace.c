
#include "../hdrs/strace.h"

static t_trap	st_trapPid(pid_t pid, int* status)
{
	int		signal;

	while (1) {
		(void)ptrace(PTRACE_SYSCALL, pid, NULL, NULL);
		if (waitpid(pid, status, 0) < 0)
			fatal(ERR_WAIT);

		if (WIFSTOPPED(*status)) {
			signal = WSTOPSIG(*status);
			if (signal & SYSCAL_MASK)
				return (syscall_);
			else
				return (signal_);
		}
		if (WIFEXITED(*status) || WIFSIGNALED(*status))
			return (exit_);
	}
}

static int	st_trace(pid_t pid)
{
	t_trap	trap;
	int 	status;
	int 	ret;

	if (ptrace(PTRACE_SEIZE, pid, NULL, OPTION_PTRACE))
		fatal(ERR_TRAC);

	do {
		trap = st_trapPid(pid, &status);
		if (trap == syscall_)
			printf("Syscall\n");
		else if (trap == signal_)
			printf("Signal_");
	} while (trap != exit_);

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

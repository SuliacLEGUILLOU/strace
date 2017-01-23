
#include "../hdrs/strace.h"

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
		wait(0);
		ret = 0;
	}
	return (ret);
}

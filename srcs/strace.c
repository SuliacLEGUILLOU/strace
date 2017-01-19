
#include "strace.h"

int		strace(const char** cmd, const char** env)
{
	char*	bin;
	pid_t	pid;
	int	ret;

	ret = 0;
	bin = cmd[0];		// Check to match against PATH
	if (access(bin, X_OK))	// Test to be done on previous line
		return (1);	// Need error management
	
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0){
		execve(bin, cmd, env);
		exit(1);
	}
	else {
		wait(-1);
		ret = 0;
	}
	return (ret);
}

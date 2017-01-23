//
// Created by s18 on 1/19/17.
//

#include <sys/stat.h>
#include "../hdrs/strace.h"

static char*	st_explore_path(const char* cmd, const char* path)
{
	struct stat		statbuff;
	char*			exp_path;
	char			test_path[100] = {'\0'};

	exp_path = strchr(path, '=');
	if (!exp_path)
		return (NULL);
	exp_path = strtok(exp_path + 1, ":");
	while (exp_path) {
		strncpy(test_path, exp_path, 98);
		strcat(test_path, "/");
		strncat(test_path, cmd, 98 - strlen(test_path));
		stat(test_path, &statbuff);
		if (!access(test_path, X_OK) && S_ISREG(statbuff.st_mode))
			return (strdup(test_path));
		exp_path = strtok(NULL, ":");
	}
	return (NULL);
}

char	*getpath(const char* cmd, const char** env)
{
	char*	path;

	if (!access(cmd, X_OK))
		return (strdup(cmd));
	while (env && *env && strncmp(*env, "PATH=", 5))
		env++;
	if (!env || !(*env))
		return (NULL);
	path = st_explore_path(cmd, *env);
	if (!path)
		return (NULL);		// ERROR
	return (path);
}
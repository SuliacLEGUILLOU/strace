
#include "../hdrs/strace.h"

static void	st_show_usage()
{
	fprintf(stderr, "Usage: %s BINARY [ARGS]\n", PROGRAM_NAME);
}

int main(int ac, char **av, char **env)
{
	int	status = EXIT_FAILURE;

	if (ac < 2) 
		st_show_usage();
	else
		status = strace(av + 1, env);
	return (status);
}

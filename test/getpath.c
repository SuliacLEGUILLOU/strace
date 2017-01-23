//
// Created by s18 on 1/21/17.
//

#include "../hdrs/strace.h"

int 	main(int ac, char** av, char** env)
{
	printf("/bin/ls %s\n", getpath("/bin/ls", env));
	printf("/bin/ls(NULL) %s\n", getpath("/bin/ls", NULL));
	printf("ls %s\n", getpath("ls", env));
	printf("ls(NULL) %s\n", getpath("ls", NULL));
	printf("lolnope %s\n", getpath("lolnop", env));
	printf("lolnope(NULL) %s\n", getpath("lolnop", NULL));
	printf("bufferoverflow %s\n", getpath("//////////////////////////////////////////////////////////////////////////////////////////////ls", env));
	return (0);
}
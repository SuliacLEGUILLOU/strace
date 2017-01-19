
#pragma once


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>

#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PROGRAM_NAME	"ft_strace"

int	strace(const char** av, const char** env);

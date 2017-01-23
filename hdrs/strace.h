
#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>

#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/wait.h>

# include "error.h"

#define PROGRAM_NAME	"ft_strace"

#define OPTION_PTRACE	PTRACE_O_TRACESYSGOOD
#define SYSCAL_MASK		0x80

enum	e_trap {
	exit_,
	syscall_,
	signal_
};
typedef enum e_trap		t_trap;

int		strace(const char** av, const char** env);
char	*getpath(const char* cmd, const char** env);

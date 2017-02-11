
#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>
#include <ctype.h>

#include <sys/stat.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "error.h"

#define PROGRAM_NAME	"ft_strace"

#define OPTION_PTRACE	PTRACE_O_TRACESYSGOOD
#define SYSCALL_MASK	0x80

#define STR_MAX_SIZE	32

#define ARGC_MAX		6
#define SYSCALL_COUNT	314

enum	e_trap {
	exit_,
	syscall_,
	signal_
};

enum	e_type {
	int_,
	uint_,
	long_,
	ulong_,
	pointer_,
	string_,
	array_,
};

typedef enum e_trap		t_trap;
typedef enum e_type 	t_type;

typedef void*			t_syscall_arg;
typedef struct			s_syscall_info
{
	const char*		name;
	t_type			ret_type;
	__uint8_t		arg_count;
	t_type			arg_type[ARGC_MAX];
}						t_syscall_info;

int		strace(const char** av, const char** env);
char	*getpath(const char* cmd, const char** env);

long	get_usr(pid_t pid, long offset);
void*	get_val(pid_t pid, t_type t, long data);
void	get_arg(pid_t pid, long syscall, t_syscall_arg* info);

int		null_byes_in_word(long word);
int		get_exit_code(int status);

const t_syscall_info*	get_syscall_info(long id);

void	print_syscall(const t_syscall_info* syscall, t_syscall_arg *arg, void* ret);

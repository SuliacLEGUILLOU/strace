//
// Created by s18 on 2/10/17.
//

#include "../hdrs/strace.h"

void	print_syscall(const t_syscall_info* syscall, t_syscall_arg *arg, void* ret)
{
	char	*convention[] = {
			"%d",
			"%u",
			"%ld",
			"%lu",
			"%p",
			"\"%s\""
	};

	printf("%s(", syscall->name);
	for (__uint8_t i = 0; i < syscall->arg_count; ++i) {
		if (i)
			printf(", ");
		if (syscall->arg_type[i] != array_)
		printf(convention[syscall->arg_type[i]], arg[i]);
	}
	printf(") = ");
	printf(convention[syscall->ret_type], ret);
	printf("\n");
}

#include "../hdrs/strace.h"

long	get_usr(pid_t pid, long offset)
{
	long	user;

	errno = 0;
	user = ptrace(PTRACE_PEEKUSER, pid, sizeof(long) * offset, NULL);
	if (user == -1 && errno)
		fatal(ERR_USER);
	return (user);
}

static long		st_get_data(pid_t pid, long off)
{
	long	data;

	errno = 0;
	data = ptrace(PTRACE_PEEKDATA, pid, off, NULL);
	if (data == -1 && errno)
		fatal(ERR_DATA);
	return (data);
}

static void*	st_get_str(pid_t pid, long addr)
{
	char			buff[STR_MAX_SIZE + 1] = {'\0'};
	unsigned int	i = 0;
	long			data;

	do {
		data = st_get_data(pid, addr + i);
		memcpy(buff + i, &data, sizeof(long));
		i += sizeof(long);
	} while ((i < STR_MAX_SIZE) & !null_byes_in_word(data));
	return (strdup(buff));
}

static char**	st_get_array(pid_t pid, long addr)
{
	char**			buff = malloc(sizeof(char*) * 256);
	unsigned int	i = 0;
	long			data;

	do {
		data = st_get_data(pid, addr + 1);
		buff[i] = data ? st_get_str(pid, addr + i) : NULL;
		++i;
	} while ((data != 0) & (i < 256));
	return (buff);
}

void	*get_val(pid_t pid, t_type t, long data)
{
	void*	ret;

	ret = NULL;
	if (t == int_ || t == uint_ || t == long_ || t == ulong_ || t == pointer_)
		ret = (void*)data;
	else if (t == string_)
		ret = st_get_str(pid, data);
	else if (t == array_)
		ret = st_get_array(pid, data);
	return (ret);
}

void	get_arg(pid_t pid, long syscall, t_syscall_arg* info)
{
	static long				REGISTER[ARGC_MAX] = {RDI, RSI, RDX, RCX, R8, R9};
	const t_syscall_info*	sys_info = get_syscall_info(syscall);
	long					data;

	if (info) {
		for (unsigned int i = 0; i < sys_info->arg_count; ++i) {
			data = get_usr(pid, REGISTER[i]);
			info[i] = get_val(pid, sys_info->arg_type[i], data);
		}
	}
}
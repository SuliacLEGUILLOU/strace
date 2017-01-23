//
// Created by s18 on 1/21/17.
//

#ifndef STRACE_ERROR_H
# define STRACE_ERROR_H

# include <errno.h>

# define ERR_FORK	"fork error"
# define ERR_EXEC	"exec error"

void	fatal(const char* msg);

#endif

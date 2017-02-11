//
// Created by s18 on 1/21/17.
//

#pragma once
#include <errno.h>

#define ERR_FORK	"fork error"
#define ERR_EXEC	"exec error"
#define ERR_WAIT	"Wait error"
#define ERR_TRAC	"Ptrace error"
#define ERR_USER	"Ptrace Get user error"
#define ERR_DATA	"Ptrace Get data error"

void	fatal(const char* msg);

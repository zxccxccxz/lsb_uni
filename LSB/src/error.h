#pragma once
#include <stdio.h>
#include <stdarg.h>

void warning_msg(const char* fmt, ...);
void error_exit(const char* fmt, ...);
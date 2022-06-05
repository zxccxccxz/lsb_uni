#include "error.h"

void warning_msg(const char* fmt, ...){
	va_list args;
	va_start(args, fmt);

	printf("error: ");
	vfprintf(stderr, fmt, args);

	va_end(args);
}

void error_exit(const char* fmt, ...){
	va_list args;
	va_start(args, fmt);

	printf("error: ");
	vfprintf(stderr, fmt, args);
	printf("exit(1);\n");

	va_end(args);

	exit(1);
}
#include "error.h"

#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define MAXSIZE 256

void error (char* format, ...){
	char buf[MAXSIZE];
	va_list args;
	va_start(args,format);
	vsprintf(buf,format,args);
	printf("*** ERROR: %s\n",buf);
	va_end(args);
	ShowWindow(GetConsoleWindow(),SW_MINIMIZE);
	ShowWindow(GetConsoleWindow(),SW_NORMAL);
}

void fatal (char* format, ...){
	char buf[MAXSIZE];
	va_list args;
	va_start(args,format);
	vsprintf(buf,format,args);
	printf("!!! FATAL ERROR: %s\n",buf);
	va_end(args);
	ShowWindow(GetConsoleWindow(),SW_MINIMIZE);
	ShowWindow(GetConsoleWindow(),SW_NORMAL);
	scanf("%c", &buf);
	exit(1);
}

void message (char* format, ...){
	char buf[MAXSIZE];
	va_list args;
	va_start(args,format);
	vsprintf(buf,format,args);
	printf("* %s\n",buf);
	va_end(args);
}

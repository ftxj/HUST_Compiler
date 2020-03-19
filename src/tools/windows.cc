/**
 * File: windows.cc
 * ---------------
 * Extra functions needed for Windows compatibility
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* This function is used to determine whether or not more files exist
 * to scan after one has been read.  This function says that no extra files
 * will be used.
 */
extern "C" int yywrap() {
	return 1;
}

/* This function from <unistd.h> is supposed to say whether a file descriptor
 * corresponds to the terminal or not.  We're going to say that everything
 * represents the terminal, which is a Totally Awful Hack but works for our
 * purposes.
 */
int isatty(int) {
	return 1;
}

char *winstrdup(const char *__str)
{
	char *str = (char *)malloc(strlen(__str) + 1);

	if (str)
		strcpy(str, __str);
	return str;
}
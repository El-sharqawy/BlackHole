// External Libs
#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN // Strips out rarely used stuff (like DDE, Shell, etc.)
	#endif
#endif

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <errno.h>
#include <sys/stat.h>
#include <assert.h>
#include <xmmintrin.h> // SSE

#define syserr(...) fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr);
#define syslog(...) fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); fflush(stdout);

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void printfflush (const char *format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
}

int SLEEP_MS(int ms) {
	struct timespec t;
	t.tv_sec = ms / 1000;
	t.tv_nsec = (ms % 1000) * 1e6;
	return nanosleep(&t, NULL);
}




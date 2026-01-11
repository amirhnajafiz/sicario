#include "logging.h"
#include "utils.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

// write a message into the stdout as log.
void log_info(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    fprintf(stdout, "%s [info] ", current_timestamp());
    vfprintf(stdout, fmt, args);
    fprintf(stdout, "\n");

    va_end(args);
}

// write a message into the stderr as log.
void log_fatal(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "%s [fatal] ", current_timestamp());
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);
}

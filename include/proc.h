#ifndef INCLUDED_PROC
#define INCLUDED_PROC

#include <stdbool.h>

// proc metadata holds the data from a process.
typedef struct
{
    int pid;
    int err;
    char *procname;
    char *state;
} proc_metadata;

// refer to src/proc.c
bool proc_exists(int pid);
bool proc_io_available(int pid);
proc_metadata *get_proc_metadata(int pid);

#endif

#ifndef INCLUDED_PROC
#define INCLUDED_PROC

#include <stdbool.h>

// proc metadata holds the data from a process.
struct proc_metadata
{
    int pid;
    char *procname;
    char *state;
};

// refer to src/proc.c
bool proc_exists(int pid);
bool proc_io_available(int pid);
struct proc_metadata *get_proc_metadata(int pid);

#endif

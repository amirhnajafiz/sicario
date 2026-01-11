#include "proc.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// proc exists checks if the process exists.
bool proc_exists(int pid)
{
    char *path = (char *)malloc(32 * sizeof(char));
    sprintf(path, "/proc/%d/stat", pid);

    FILE *file;
    if ((file = fopen(path, "r")) != NULL)
    {
        return true;
    }

    return false;
}

// proc io available checks if the process exposes its IO metrics.
bool proc_io_available(int pid)
{
    char *path = (char *)malloc(32 * sizeof(char));
    sprintf(path, "/proc/%d/io", pid);

    FILE *file;
    if ((file = fopen(path, "r")) != NULL)
    {
        return true;
    }

    return false;
}

// get process metadata from its stat file in proc filesystem.
struct proc_metadata *get_proc_metadata(int pid)
{
    struct proc_metadata* metadata = (struct proc_metadata*)malloc(sizeof(struct proc_metadata));
    metadata->pid = pid;

    return metadata;
}

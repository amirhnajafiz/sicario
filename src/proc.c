#include "proc.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// proc exists checks if the process exists.
// the target file is /proc/<pid>/stat.
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
// the target file is /proc/<pid>/io.
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
proc_metadata *get_proc_metadata(int pid)
{
    // create a metadata instance
    proc_metadata* metadata = (proc_metadata*)malloc(sizeof(proc_metadata));
    metadata->pid = pid;
    metadata->procname = (char *)malloc(100 * sizeof(char));
    metadata->state = (char *)malloc(4 *sizeof(char));
    metadata->err = 0;

    // open the stat file
    char *path = (char *)malloc(32 * sizeof(char));
    sprintf(path, "/proc/%d/stat", pid);

    FILE *file;
    if ((file = fopen(path, "r")) == NULL)
    {
        metadata->err = 1;
        return metadata;
    }

    // read the file content (only second and third strings)
    char *token = (char *)malloc(100 * sizeof(char));
    int index = 0;
    while (fscanf(file, "%99s", token) == 1)
    {
        index++;
        if (index == 2)
        {
            strcpy(metadata->procname, token);
            ctrim_str(metadata->procname);
        }
        if (index == 3)
        {
            strcpy(metadata->state, token);
            break;
        }
    }

    return metadata;
}

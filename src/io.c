#include "io.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// get IO metrics from proc filesystem.
// target is /proc/<pid>/io.
io_metrics *get_io_metrics(int pid)
{
    // create a io metrics instance
    io_metrics *metrics = (io_metrics *)malloc(sizeof(io_metrics));
    metrics->err = 0;

    // open the io file
    char *path = (char *)malloc(32 * sizeof(char));
    sprintf(path, "/proc/%d/io", pid);

    FILE *file;
    if ((file = fopen(path, "r")) == NULL)
    {
        metrics->err = 1;
        return metrics;
    }

    // read the file line by line
    char *buffer = (char *)malloc(128 * sizeof(char));
    while (fgets(buffer, 128, file) != NULL)
    {
        if (has_prefix(buffer, "write_bytes"))
        {
            char *token = strtok(buffer, IO_DELIMETER);
            token = strtok(NULL, IO_DELIMETER);

            metrics->write_bytes = strtoul(token, NULL, 10);
        }
        else if (has_prefix(buffer, "read_bytes"))
        {
            char *token = strtok(buffer, IO_DELIMETER);
            token = strtok(NULL, IO_DELIMETER);

            metrics->read_bytes = strtoul(token, NULL, 10);
        }
        else if (has_prefix(buffer, "syscr"))
        {
            char *token = strtok(buffer, IO_DELIMETER);
            token = strtok(NULL, IO_DELIMETER);

            metrics->syscr = strtoul(token, NULL, 10);
        }
        else if (has_prefix(buffer, "syscw"))
        {
            char *token = strtok(buffer, IO_DELIMETER);
            token = strtok(NULL, IO_DELIMETER);

            metrics->syscw = strtoul(token, NULL, 10);
        }
    }

    // free the resources
    fclose(file);
    free(path);

    return metrics;
}

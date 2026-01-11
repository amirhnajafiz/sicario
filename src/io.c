#include "io.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// storing the last snapshot to calculate the rate values
io_metrics *last_snapshot = NULL;

// get IO metrics from proc filesystem.
// target is /proc/<pid>/io.
io_metrics *get_io_metrics(int pid)
{
    // create a io metrics instance
    io_metrics *metrics = (io_metrics *)malloc(sizeof(io_metrics));
    metrics->err = 0;
    metrics->ts = time(NULL);
    metrics->read_rate = 0;
    metrics->write_rate = 0;

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

    // update rates based on last snapshot
    if (last_snapshot != NULL)
    {
        int delta_time = metrics->ts - last_snapshot->ts;
        metrics->read_rate = (metrics->read_bytes - last_snapshot->read_bytes) / delta_time;
        metrics->write_rate = (metrics->write_bytes - last_snapshot->write_bytes) / delta_time;
    }

    free(last_snapshot);
    last_snapshot = metrics;

    // free the resources
    fclose(file);
    free(path);

    return metrics;
}

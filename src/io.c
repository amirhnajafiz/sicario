#include "io.h"

#include <stdio.h>
#include <stdlib.h>

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

    return metrics;
}

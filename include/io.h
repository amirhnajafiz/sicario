#ifndef INCLUDED_IO
#define INCLUDED_IO

#include <time.h>

#define IO_DELIMETER ": "

// IO metrics holds the read/write metrics values.
typedef struct
{
    int err;
    unsigned long long read_bytes;
    unsigned long long write_bytes;
    unsigned long long syscr;
    unsigned long long syscw;
    float read_rate;
    float write_rate;
    time_t ts;
} io_metrics;

// refer to src/io.c
io_metrics *get_io_metrics(int pid);

#endif

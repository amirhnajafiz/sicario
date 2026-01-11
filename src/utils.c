#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// pid validation checks if pid is a valid non-negative number.
bool pid_validation(char *pid_str)
{
    // copy the input
    char *ptr = pid_str;

    while(*ptr != '\0')
    {
        bool flag = false;
        for (int i = 0; i < PID_VALIDATION_LEN; i++)
        {
            if (PID_VALIDATION[i] == *ptr)
            {
                flag = true;
                break;
            }
        }

        if (!flag)
            return false;
        
        ptr++;
    }

    return true;
}

// get the pid number from string.
int pid_from_str(char *pid_str)
{
    return pid_validation(pid_str) ? atoi(pid_str) : -1;
}

#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

// pid validation checks if pid is a valid positive number.
bool pid_validation(char *pid_str)
{
    // copy the input
    char *ptr = pid_str;

    while (*ptr != '\0')
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

// ctrim string removes '(' and ')' from both sides of a string.
void ctrim_str(char *str)
{
    int len = strlen(str);
    if (len < 2)
    {
        return;
    }

    if (str[len - 1] == ')')
    {
        str[len - 1] = '\0';
        len--;
    }

    if (str[0] == '(')
    {
        for (int i = 0; i < len - 1; i++)
        {
            str[i] = str[i + 1];
        }

        str[len - 1] = '\0';
    }
}

// has prefix checks if a string contains a substring.
bool has_prefix(const char *str, const char *pre)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

// current timestamp returns timestamp as string.
char *current_timestamp()
{
    time_t rawtime;
    struct tm *timeinfo;

    char *buffer = (char *)malloc(64 * sizeof(char));

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo); 
    
    return buffer;
}

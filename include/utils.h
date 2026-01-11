#ifndef INCLUDED_UTILS
#define INCLUDED_UTILS

// pid validation rules to check if pid is a valid positive number
#define PID_VALIDATION "0123456789"
#define PID_VALIDATION_LEN 10

// refer to src/utils.c
int pid_from_str(char *pid_str);

#endif

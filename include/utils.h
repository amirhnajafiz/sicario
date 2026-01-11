#ifndef INCLUDED_UTILS
#define INCLUDED_UTILS

#include <stdbool.h>

// pid validation rules to check if pid is a valid positive number
#define PID_VALIDATION "0123456789"
#define PID_VALIDATION_LEN 10

// refer to src/utils.c
int pid_from_str(char *pid_str);
bool has_prefix(const char *str, const char *pre);
void ctrim_str(char *str);
char *current_timestamp();

#endif

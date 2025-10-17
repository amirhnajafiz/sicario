/* cmd.c */
#include "cmd.h"

int execute_command(const char *cmd) {
    /* 
        Execute a system command and handle errors.
    */
    int rc = system(cmd);
    if (rc != 0) {
        fprintf(stderr, "Failed to run command (rc=%d): %s\n", rc, cmd);
    }

    return rc;
}

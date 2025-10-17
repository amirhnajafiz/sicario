#include "sicario.h"

void prepare_rootfs_files() {
    /* 
        Prepare container's rootfs files.
        The first step is to build the ROOTFS_DIRECTORY.
    */
    const char *path = ROOTFS_DIRECTORY;
    size_t len = strlen(path);
    size_t qsize = len * 4 + 3; /* room for escaping single quotes */
    char *quoted = malloc(qsize + 1);
    if (!quoted) { perror("malloc"); exit(1); }

    char *dst = quoted;
    *dst++ = '\'';
    for (size_t i = 0; i < len; ++i) {
        if (path[i] == '\'') {
            memcpy(dst, "'\\''", 4);
            dst += 4;
        } else {
            *dst++ = path[i];
        }
    }
    *dst++ = '\'';
    *dst = '\0';

    size_t cmdsize = qsize + 32;
    char *cmd = malloc(cmdsize);
    if (!cmd) { perror("malloc"); free(quoted); exit(1); }

    // create the rootfs directory
    snprintf(cmd, cmdsize, "sudo mkdir -p %s", quoted);
    int rc = system(cmd);
    if (rc != 0) {
        fprintf(stderr, "Failed to run command (rc=%d): %s\n", rc, cmd);
    }

    free(cmd);
    free(quoted);

    // copy the alpine image filesystem into the rootfs directory
    const char *alpine_image = ALPINE_IMAGE;
    cmdsize = strlen(alpine_image) + strlen(ROOTFS_DIRECTORY) + 32;
    cmd = malloc(cmdsize);
    if (!cmd) { perror("malloc"); exit(1); }

    snprintf(cmd, cmdsize, "sudo tar -xzf %s -C %s", alpine_image, ROOTFS_DIRECTORY);
    rc = system(cmd);
    if (rc != 0) {
        fprintf(stderr, "Failed to run command (rc=%d): %s\n", rc, cmd);
    }

    free(cmd);
}

int main() {
    printf("Container directory: %s\n", CONTAINER_DIRECTORY);
    printf("Root filesystem directory: %s\n", ROOTFS_DIRECTORY);

    prepare_rootfs_files();

    return 0;
}

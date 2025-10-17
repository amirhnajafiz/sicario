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

    // update the /etc/hosts, /etc/hostname, and /etc/resolv.conf files in the rootfs
    const char *hosts_content = "127.0.0.1\tlocalhost\n"
                                "::1\tlocalhost ip6-localhost ip6-loopback\n";
    const char *hosts_path = ROOTFS_DIRECTORY "/etc/hosts";
    FILE *hosts_file = fopen(hosts_path, "w");
    if (hosts_file) {
        fputs(hosts_content, hosts_file);
        fclose(hosts_file);
    } else {
        perror("fopen hosts");
    }

    const char *hostname_content = CONTAINER "\n";
    const char *hostname_path = ROOTFS_DIRECTORY "/etc/hostname";
    FILE *hostname_file = fopen(hostname_path, "w");
    if (hostname_file) {
        fputs(hostname_content, hostname_file);
        fclose(hostname_file);
    } else {
        perror("fopen hostname");
    }

    // copy the host's resolv.conf to the container's rootfs
    const char *resolv_src = "/etc/resolv.conf";
    const char *resolv_dst = ROOTFS_DIRECTORY "/etc/resolv.conf";
    cmdsize = strlen(resolv_src) + strlen(resolv_dst) + 16;
    cmd = malloc(cmdsize);
    if (!cmd) { perror("malloc"); exit(1); }
    
    snprintf(cmd, cmdsize, "sudo cp %s %s", resolv_src, resolv_dst);
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

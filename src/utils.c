#include "utils.h"
#include "universe.h"

void addr_to_string(void* addr, char* buffer, size_t buffer_size) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "addr2line -f -e %s %p", UNIVERSE.argv[0], addr);
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        perror("popen");
    }
    fgets(buffer, buffer_size, fp);
    pclose(fp);
    // Remove newline character if present
    size_t len = strlen(buffer);
    if (len && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

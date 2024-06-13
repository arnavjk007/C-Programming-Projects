#include "hash.h"
#include "ll.h"

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv) {
    (void) argc;
    (void) argv;
    int line_count = 0;
    char buffer[1024];
    while ((fgets(buffer, sizeof(buffer), stdin)) != NULL) {
        line_count++;
    }
    printf("%d\n", line_count);
    return 0;
}

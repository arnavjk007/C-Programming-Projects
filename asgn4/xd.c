#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
bool isvalid(char c) {
    return 32 <= c && 126 >= c;
}
void printLine(int size, unsigned char buffer[], int count) {
    printf("%08x: ", size);
    for (int i = 0; i < 16; i++) {
        if (i < count)
            printf("%02x", buffer[i]);
        else
            printf("  ");
        if (i % 2 == 1) {
            printf(" ");
        }
    }
    printf(" ");
    for (int i = 0; i < 16; i++) {
        if (i < count)
            printf("%c", isvalid(buffer[i]) ? buffer[i] : '.');
    }
    printf("\n");
}

int main(int argc, char **argv) {
    char *filename = argv[1];
    if (argc != 2 && argc != 1) {
        exit(0);
    }
    int fd = argc == 1 ? 0 : open(filename, O_RDONLY);
    ssize_t size = 0;
    if (fd == -1) {
        exit(1);
    }
    ssize_t res;
    unsigned char buffer[32] = { 0 };
    unsigned char temp[16] = { 0 };
    int count = 0;
    while ((res = read(fd, temp, 16)) > 0) {

        for (int i = 0; i < res; i++) {
            buffer[count + i] = temp[i];
        }

        count += (int) res;
        if (count >= 16) {
            printLine((int) size, buffer, 16);
            size += 16;
            count -= 16;
            for (int i = 0; i < count; i++) {
                buffer[i] = buffer[i + 16];
            }
        }
    }
    if (count > 0) {
        printLine((int) size, buffer, count);
    }
    return 0;
}

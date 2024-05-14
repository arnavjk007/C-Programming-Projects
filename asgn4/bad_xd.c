#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define m 16
void p(ssize_t s, unsigned char b[], int c) {
    printf("%08zx: ", s);
    for (int i = 0; i < m; i++)
        i < c ? printf("%02x", b[i]) : printf("  "), printf(i % 2 ? " " : "");
    printf(" ");
    for (int i = 0; i < c; i++)
        printf("%c", 31 < b[i] && b[i] < 127 ? b[i] : '.');
    printf("\n");
}
int main(int n, char **v) {
    int i, c = 0, f = n < 2 ? 0 : open(v[1], O_RDONLY);
    ssize_t B, s = 0;
    unsigned char b[32], t[m];
    if (f < 0)
        exit(1);
    while ((B = read(f, t, m))) {
        for (i = 0; i < B; i++)
            b[c + i] = t[i];
        c += B;
        if (c >= m) {
            p(s, b, m), s += m, c -= m;
            for (i = 0; i < c; i++)
                b[i] = b[i + m];
        }
    }
    c ? p(s, b, c) : exit(0);
}

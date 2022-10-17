#include <stdio.h>
#include <windows.h>

int main() {
    unsigned int size = 1000 * 1024 * 1024;
    char *buff;
    int i = 0;
    while (1) {
        buff = (char *) VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        i++;
        printf("%p\n", buff);
        for (int i = 0; i < 1000 * 1024 * 1024; i += 4096) {
            buff[i] = 0;
        }
    }
}

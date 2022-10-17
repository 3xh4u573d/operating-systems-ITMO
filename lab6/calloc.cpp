#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
    long long *memory;
    clock_t start, end;
    int size;
    for (int i = 1; i <= 30; i++){
        size = 1<<i;
        start = clock();
        for (int i = 0; i < 100000; i++){
            memory = (long long*)calloc(size, sizeof(int));
            free(memory);
        }
        end = clock();
        double time_in_sec = (double)(end-start) / CLOCKS_PER_SEC;
        printf("Size: %d B  Time:%f sec\n", size, time_in_sec);
    }
    return 0;
}

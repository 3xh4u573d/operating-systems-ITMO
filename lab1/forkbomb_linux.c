#include <unistd.h>
#include <stdlib.h>
int main(){
    while(1) {
        fork();
        system("ps aux | wc -l >> logs.txt ");
        system("ps aux | wc -l");
    }
}

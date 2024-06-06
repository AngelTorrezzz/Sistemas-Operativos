#include <stdio.h>
#include <stdlib.h>

int main(){
    int *var = malloc(sizeof(int));
    int k = 0;
    printf("%d,        %d\n", getpid(), gettid());
    while (1){
        int *var = malloc(sizeof(int)*10000000);
        printf("S\n");
        sleep(1);
    }
    
    return 0;
}
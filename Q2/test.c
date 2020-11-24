#include "workload.c"
#include <stdio.h>

int main(){
    int hits = 69;
    int size = 143;
    float x = (float)hits * 100 / size;

    printf("%f\n", x);

    return 0;
}
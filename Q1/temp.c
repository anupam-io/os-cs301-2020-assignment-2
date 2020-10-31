#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){   
    int rows = 2;
    char **c = calloc(rows, sizeof(char*));
    c[0] = "cat"; c[1] = NULL;

    rows++; c = calloc(rows, sizeof(char*));
    c[1] = "dog"; c[2] = NULL;

    rows++; c = calloc(rows, sizeof(char*));
    c[2] = "mouse"; c[3] = NULL;

    int i = 0;
    while(c[i]){
        printf("%s\n", c[i++]);
    }




    // char *str;
    // str = (char*)malloc(15);
    // strcpy(str, "tutorialspoint");


    return 0;
}
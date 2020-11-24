#include <stdio.h>
#include <stdlib.h>

int main(){
    char** list = NULL;

    list = malloc(sizeof(char*));
    list[0] = "Word 1";
    
    list = realloc(list, 2);
    list[1] = "Word 2";

    for(int i = 0; list[i]; i++){
        printf("%s\n", list[i]);
        // free(list[i]);
    }

    free(list);
        
    return 0;
}

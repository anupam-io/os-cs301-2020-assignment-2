#include <stdio.h>
#include <stdlib.h>
#include "trie.c"

int main(int argc, char* argv[]){
    trie_t my_trie = init_trie();
    insert(my_trie, "cat", 10);
    insert(my_trie, "india", 10);
    insert(my_trie, "brain", 10);
    insert(my_trie, "whole", 10);
    insert(my_trie, "iamthedoghere", 10);
    insert(my_trie, "whoidthedoghere", 10);

    int abcd = 99;
    int* waste = &abcd;
    
    printf("%d\n", find(my_trie, "india", waste));
    printf("%d\n", find(my_trie, "nothere", waste));


    

    printf("%d\n", find(my_trie, "brain", waste));
    delete_kv(my_trie, "brain");
    printf("%d\n", find(my_trie, "brain", waste));


    
    
    delete_trie(my_trie);
    printf("%d\n", my_trie->head == NULL);

    // printf("\n");
    return 0;
}

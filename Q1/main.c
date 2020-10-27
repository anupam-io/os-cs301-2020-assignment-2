#include <stdio.h>
#include <stdlib.h>
#include "trie.c"

void show_node(trie_node_t x){
    if(!x) return;
    
    printf("%d - ", x->value);
    for(int i = 0; i<ALP_SIZE; i++){
        if(x->children[i]){
            show_node(x->children[i]);
        }
    }
}


int main(int argc, char* argv[]){
    trie_t my_trie = init_trie();

    insert(my_trie, "india", 10);
    insert(my_trie, "cat", 10);
    insert(my_trie, "brain", 10);
    insert(my_trie, "whole", 10);


    int abcd = 0;
    int* waste = &abcd;
    printf("%d", find(my_trie, "ind", waste));


    

    // show_node(my_trie->head);
    printf("\n");
    return 0;
}

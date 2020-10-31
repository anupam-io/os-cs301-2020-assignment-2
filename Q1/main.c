#include <stdio.h>
#include <stdlib.h>
#include "trie.c"

int main(int argc, char* argv[]){
    trie_t my_trie = init_trie();
    insert(my_trie, "cat", 100);
    insert(my_trie, "car", 100);
    insert(my_trie, "can", 100);
    insert(my_trie, "babb", 100);
    insert(my_trie, "zebra", 100);
    insert(my_trie, "carrot", 100);
    insert(my_trie, "canteen", 100);
       
    // char** output = keys_with_prefix(my_trie, "c");
    // int i = 0;
    // while(output[i]){
    //     printf("-> %s\n", output[i++]);
    // }


    // int abcd = 99;
    // int* waste = &abcd;
    
    // printf("%d\n", find(my_trie, "india", waste));
    // printf("%d\n", find(my_trie, "nothere", waste));


    

    // printf("%d\n", find(my_trie, "brain", waste));
    // delete_kv(my_trie, "brain");
    // printf("%d\n", find(my_trie, "brain", waste));


    
    
    // delete_trie(my_trie);
    // printf("%d\n", my_trie->head == NULL);

    // printf("\n");
    return 0;
}

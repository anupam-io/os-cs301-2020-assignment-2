#define _NO_HOH_LOCK_TRIE
#include <stdio.h>
// #define _S_LOCK_TRIE
#include "trie.h"

int main(){
    trie_t t = init_trie();
    insert(t, "apple", 1);
    insert(t, "ango", 1);
    insert(t, "", 1);

    char** a;
    a = keys_with_prefix(t, "");

    int i = 0;
    while(a[i]){
        printf("<%s>\n", a[i++]);
    }

    return 0;
}

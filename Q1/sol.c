#include <stdio.h>
#include <stdlib.h>
#define ALP_SIZE 26

void _rec_auto_comp(Node* root, char* currPrefix, int currDepth, char** list, int totalWords) 
{ 
    // found a string in Trie with the given prefix 
    if (root->isWordEnd) 
    { 
        // insert currPrefix into the list
        totalWords++;
        list[totalWords - 1] = (char*)malloc(strlen(currPrefix)*sizeof(currPrefix[0]));
        list[totalWords - 1] = currPrefix;
        list[totalWords] = NULL;
    } 
  
    // All children struct node pointers are NULL 
    if (isLastNode(root)){
        return;
    } 

    for (int i = 0; i < ALP_SIZE; i++) 
    { 
        if (root->children[i]) 
        { 
            // append current character to currPrefix string 
            currPrefix[currDepth] = 'a'+i; 

            // recur over the rest 
            suggestionsRec(root->children[i], currPrefix, currDepth+1); 

            // remove last character 
            currPrefix[currDepth] = NULL; 
        } 
    } 
} 
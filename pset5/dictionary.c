/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// global variable for root that will point to our trie
node* root;
// counter of words in dictionary
int count;
// prototype for recursion in unload
void unloadNode(node* nextNode);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // declare pointer to move through trie
    node* newptr;
    // point to the root of trie
    newptr = root;
    
    // for every letter in the word check if it is in trie
    for(int i = 0; i < strlen(word); i++) 
    {
        //if there ' symbol in the word
        if (word[i] == '\'')
        {
            /* if there is no ' in trie this means that 
            there is now node for ' in our path in the dictionary and we return false */
            if(newptr->children[MAX_ALPHABET-1] == NULL) 
               return false;
            
            // if the ' exist we move forward
            else
                newptr = newptr->children[MAX_ALPHABET-1];
        }
        // check for letter from 'a' to 'z'. We transform all letters to lowcase to compare with dictionary
        else
        {
            /* if there is no such letter in trie this means that 
            there is now node for ' in our path in the dictionary and we return false */
            if(newptr->children[tolower(word[i])-'a'] == NULL) 
               return false;

            // if the letter exist we move forward to seek the signal newptr->is_word
            else
                newptr = newptr->children[tolower(word[i])-'a'];

        }
    }
    
    /* when we reach the end of word we return the value of variable is_word in node. 
    if the variable true the word exist, else not */
    return newptr->is_word;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
 

bool load(const char* dictionary)
{
    // open file with dictionary
    FILE* dict = fopen(dictionary, "r");
    // standart check of opening file
    if(!dict)
       return false;
    // define word counter to zero befor loading words in trie
    count = 0;
    
    // root will points to first node in trie, so it have no need to point somewhere alse
    root = NULL;
    //define the first node in trie
    node* newptr = (node *)malloc(sizeof(node));
    // define all parametrs of node to default. at this poin we have clear trie, so no need our children to point somewhere alse
    for (int i = 0; i < MAX_ALPHABET; i++)
    {
        newptr->children[i] = NULL;
        newptr->is_word = false;
    }
    // now root hosts our trie and start to be enter point
    root = newptr;
    
    // we go through the file dictionary to the end character by character. EOF - end of file
    for(int c = fgetc(dict); c != EOF; c = fgetc(dict)) 
    {
        // check condition for ' symbol
        if (c == '\'')
        {
            if(newptr->children[MAX_ALPHABET-1] == NULL) 
            {
                newptr->children[MAX_ALPHABET-1] = (node *)malloc(sizeof(node));
                newptr = newptr->children[MAX_ALPHABET-1];
                // define all parametrs of node to default. at this poin we have clear trie, so no need our children to point somewhere alse
                for (int i = 0; i < MAX_ALPHABET; i++)
                {
                    newptr->children[i] = NULL;
                    newptr->is_word = false;
                }
                
            }

            else
                newptr = newptr->children[MAX_ALPHABET-1];
        }  
        
        // 10 is '\n' in decimal. check condition for letters from 'a' to 'z'. 
        else if (c != '\'' && c != 10)
        {
            // if there no node for letter we need to create it
            if(newptr->children[tolower(c)-'a'] == NULL) 
            {
                newptr->children[tolower(c)-'a'] = (node *)malloc(sizeof(node));
                newptr = newptr->children[tolower(c)-'a']; 
                // define all parametrs of node to default. at this poin we have clear trie, so no need our children to point somewhere alse
                for (int i = 0; i < MAX_ALPHABET; i++)
                {
                    newptr->children[i] = NULL;
                    newptr->is_word = false;
                }
            }
            else
                newptr = newptr->children[tolower(c)-'a'];
        }  
        
        else
        {
            newptr->is_word = true;
            newptr = root;
            count++;
        }
    }
        

    //close dictionary file
    fclose(dict);
    
    return true;
    
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return count;
}

/**
 * Frees the memory used by this node and all nodes within it's children
 */
void unloadNode(node* nextNode)
{
    // call unloadNode on every node in this node's children
    for(int i = 0; i < MAX_ALPHABET; i++)
    {
        if(nextNode->children[i] != NULL)
        {
            unloadNode(nextNode->children[i]);
        }
    }
    
    // once the children nodes are freed, free this node
    free(nextNode);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // call the recursive algorithm 'unloadNode', starting with the root
    unloadNode(root);
    return true;
}


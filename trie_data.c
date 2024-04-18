#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int count;  // Count of how many times this word has been inserted
};

// Inserts the word into the trie
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *pCrawl = root;
    while (*word) {
        int index = CHAR_TO_INDEX(*word);
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = (struct TrieNode *)malloc(sizeof(struct TrieNode));
            memset(pCrawl->children[index], 0, sizeof(struct TrieNode));  // Clear allocated memory
        }
        pCrawl = pCrawl->children[index];
        word++;
    }
    pCrawl->count++;  // Increment the count at the end of the word
}


// Computes the number of occurrences of the word in the trie
int numberOfOccurances(struct TrieNode *root, char *word) {
    struct TrieNode *pCrawl = root;
    while (*word) {
        int index = CHAR_TO_INDEX(*word);
        if (!pCrawl->children[index]) {
            return 0;
        }
        pCrawl = pCrawl->children[index];
        word++;
    }
    return pCrawl->count;
}

// Deallocate the trie structure
struct TrieNode *deallocateTrie(struct TrieNode *root) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            deallocateTrie(root->children[i]);
        }
    }
    free(root);
    return NULL;
}

// Initializes a trie structure
struct TrieNode *createTrie() {
    struct TrieNode *root = (struct TrieNode *) malloc(sizeof(struct TrieNode));
    if (root) {
        memset(root, 0, sizeof(struct TrieNode));
    }
    return root;
}

// Placeholder function for reading dictionary and loading words
int readDictionary(char* filename, char** pInWords) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }
    int numWords;
    fscanf(file, "%d", &numWords);
    char buffer[100];
    for (int i = 0; i < numWords; i++) {
        fscanf(file, "%s", buffer);
        pInWords[i] = strdup(buffer);
    }
    fclose(file);
    return numWords;
}


int main(void)
{
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode *pTrie = createTrie();
    for (int i = 0; i < numWords; i++)
    {
        insert(pTrie, inWords[i]);
    }
// parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
        printf("There is an error in this program\n");

    return 0;
}

// Bryant Parchinski
// 04/19/2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
    struct Trie *children[26];
    int count; // Count of words ending at this node
};

// Initializes a trie structure
struct Trie *createTrie() {
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    node->count = 0;
    return node;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createTrie();
        }
        current = current->children[index];
    }
    current->count++; // Increment the count of the word
}

// Computes the number of occurrences of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            return 0; // Word not found
        }
        current = current->children[index];
    }
    return current->count;
}

// Deallocates the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie != NULL) {
        for (int i = 0; i < 26; i++) {
            if (pTrie->children[i] != NULL) {
                deallocateTrie(pTrie->children[i]);
            }
        }
        free(pTrie);
    }
    return NULL;
}

// Reads the dictionary file and loads words into pInWords
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Failed to open file\n");
        return 0;
    }
    int numWords;
    fscanf(file, "%d", &numWords); // the first line contains the number of words
    for (int i = 0; i < numWords; i++) {
        pInWords[i] = (char *)malloc(100); // allocate memory for each word
        fscanf(file, "%s", pInWords[i]);
    }
    fclose(file);
    return numWords;
}

// Main unchanged
int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}


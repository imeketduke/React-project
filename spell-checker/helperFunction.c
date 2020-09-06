#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h> // free дитн функция ушин
#include "header.h"

typedef struct node
{
	bool isWord;
	struct node *children[26];
} node;

int resSize = 0;
node *root;

bool zagruzka()
{
	// initialize trie
	root = malloc(sizeof(node));
	if (root == NULL)
	{
		return false;
	}
	root->isWord = false;
	for (int i = 0; i < 26; i++)
	{
		root->children[i] = NULL;
	}

	FILE *file = fopen("words.txt", "r");
	if (file == NULL)
	{
		zabei();
		return false;
	}

	char word[46];
	int index;

	// insertion to trie
	while (fscanf(file, "%s", word) != EOF) // EOF = end of the file дитн
	{
		node *child = root;

		for (int i = 0, len = strlen(word); i < len; i++)
		{
			index = (int)word[i] - (int)'a';

			if (child->children[index] == NULL)
			{ // node doesn't exist
				child->children[index] = malloc(sizeof(node));
				if (child->children[index] == NULL)
				{
					return false;
				}
				child->children[index]->isWord = false;
				for (int j = 0; j < 26; j++)
				{
					child->children[index]->children[j] = NULL;
				}
			}
			child = child->children[index];
		}
		child->isWord = true;
		resSize++;
	}

	fclose(file);

	return true;
}

int size()
{
	return resSize;
}

bool check(const char *word)
{
	int index;
	node *child = root;
	for (int i = 0, len = strlen(word); i < len; i++)
	{
		index = (int)tolower(word[i]) - (int)'a';

		child = child->children[index];
		if (child == NULL)
		{
			return false;
		}
	}
	return child->isWord;
}

void breakNode(node *top)
{
	if (top == NULL)
		return;

	for (int i = 0; i < 26; i++)
	{
		if (top->children[i] != NULL)
		{
			breakNode(top->children[i]);
		}
	}
	free(top);
}

void zabei()
{
	breakNode(root);
}
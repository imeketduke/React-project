#include <stdio.h>
#include <ctype.h> // isdigit, isalnum дитндерге керек крч
#include "header.h"
#include "helperFunction.c"

int main()
{
	char *textLink = "test.txt";
	printf("Filename is : %s\n", textLink);

	// загрузка
	if (!zagruzka())
	{
		printf("There are some problems with loading\n");
		return 1;
	}

	// fileды ашу
	FILE *file = fopen(textLink, "r");
	if (file == NULL)
	{
		printf("There are some problems with opening %s\n", textLink);
		zabei();
		return 1;
	}

	// just stats
	int index = 0, misspellings = 0, words = 0;
	char word[46];

	for (int c = fgetc(file); c != EOF; c = fgetc(file))
	{
		if (isalpha(c))
		{
			word[index] = c;
			index++;

			// English languageдагы max. word length дитн 45 болганы ушин осылай 45ты алдым
			if (index > 45)
			{
				while ((c = fgetc(file)) != EOF && isalpha(c))
					;
				index = 0;
			}
		}
		else if (isdigit(c))
		{
			while ((c = fgetc(file)) != EOF && isalnum(c))
				;
			index = 0;
		}
		else if (index > 0)
		{
			word[index] = '\0';
			index = 0;
			words++;

			if (!check(word))
			{
				printf("%s\n", word);
				misspellings++;
			}
		}
	}

	fclose(file);

	zabei();

	printf("\nMisspelled words from the text     %d", misspellings);
}
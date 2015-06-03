#include "utils/line_to_wordtab.h"

#include <stdlib.h>
#include <string.h>

char	**line_to_wordtab(const char	*line)
{
	char	*pch;
	char	**wordtab;
	int index;
	
	index = 0;
	pch = strtok(line, " ");
	wordtab = (char	**)malloc(sizeof(char*) * 1);
	wordtab[0] = pch;
	
	while (pch != NULL)
	{
		pch = strtok(NULL, " ");
		index++;
		wordtab = realloc(wordtab, sizeof(char*) * (index + 1));
		wordtab[index] = pch;
	}

	index++;

	wordtab = realloc(wordtab, sizeof(char*) * (index + 1));
	wordtab[index] = NULL;

	return wordtab;
}

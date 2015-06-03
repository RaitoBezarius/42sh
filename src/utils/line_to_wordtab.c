#include "utils/line_to_wordtab.h"

#include <stdlib.h>
#include <string.h>

char	**line_to_wordtab(const char	*line)
{
	char	*pch;
	char	**wordtab;
	int index;
	int line_length;
	
	line_length = strlen(line);
	pch = (char	*)malloc(sizeof(char) * (line_length + 1));
	strcpy(pch, line);
	pch[line_length] = '\0';
	index = 0;
	pch = strtok(pch, " ");
	wordtab = (char	**)malloc(sizeof(char*) * 1);
	wordtab[0] = pch;
	
	while (pch != NULL)
	{
		pch = strtok(NULL, " ");
		index++;
		wordtab = realloc(wordtab, sizeof(char*) * (index + 1));
		wordtab[index] = pch;
	}

	return wordtab;
}

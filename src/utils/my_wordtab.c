/*
** my_wordtab.c for my_wordtab in /home/bebe-b_h/projects/tmp
** 
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.net>
** 
** Started on  Sat May  9 20:39:43 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:38:38 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "utils.h"

size_t		my_strclen(const char *str, const char c)
{
  size_t	i;

  i = 0;
  if (str)
    while (str[i] && str[i] != c)
      ++i;
  return (i);
}

size_t		count_words(const char *str, const char sep)
{
  size_t	words;
  size_t	i;

  i = 0;
  words = 0;
  if (str)
    while (str[i])
      {
	if (str[i] && str[i] != sep
	    && (str[i + 1] == '\0' || str[i + 1] == sep))
	  ++words;
	++i;
      }
  return (words);
}

char		**str_to_wordtab(const char *str, const char sep)
{
  char		**wordtab;
  size_t	i;
  size_t	y;

  if (!(wordtab = malloc(sizeof(char *) * (count_words(str, sep) + 1))))
    {
      fprintf(stderr, "error: could not allcoate memory\n");
      return (NULL);
    }
  y = 0;
  i = 0;
  while (str[i])
    {
      if ((i == 0 || str[i - 1] == sep) && str[i] != sep)
	{
	  wordtab[y] = strndup(&str[i], my_strclen(&str[i], sep));
	  ++y;
	}
      ++i;
    }
  wordtab[y] = NULL;
  return (wordtab);
}

void		free_wordtab(char **wordtab)
{
  size_t	i;

  if (!wordtab)
    return ;
  i = 0;
  while (wordtab[i])
    {
      free(wordtab[i]);
      ++i;
    }
  free(wordtab);
}

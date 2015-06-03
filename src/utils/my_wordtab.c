/*
** my_wordtab.c for my_wordtab in /home/bebe-b_h/projects/tmp
** 
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.net>
** 
** Started on  Sat May  9 20:39:43 2015 BEBE-BELL Hendy-Wilson
** Last update Mon May 11 21:50:25 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

char		**str_to_wordtab(const char *str, const char sep)
{
  char		**wordtab;
  size_t	i;
  size_t	y;

  if (!(wordtab = malloc(sizeof(char *) * (count_words(str, sep) + 1))))
    {
      ERROR(ERR_ALLOC);
      return (NULL);
    }
  y = 0;
  i = 0;
  while (str[i])
    {
      if ((i == 0 || str[i - 1] == sep) && str[i] != sep)
	{
	  wordtab[y] = strndup(&str[i], strclen(&str[i], sep));
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

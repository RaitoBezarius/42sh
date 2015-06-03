/*
** wordtab_to_str.c for 42sh in /home/bebe-b_h/rendu/42sh/src/utils
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 13:22:05 2015 BEBE-BELL Hendy-Wilson
** Last update Sun May 24 13:34:52 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>

#include "utils.h"

static int	get_string_len(char **wordtab)
{
  int		string_len;
  int		word_count;

  string_len = 0;
  word_count = 0;
  while (wordtab[word_count] != NULL)
  {
    string_len += my_strlen(wordtab[word_count]);
    ++word_count;
  }
  return (string_len + word_count);
}

char	*wordtab_to_str(char **wordtab)
{
  char	*string;
  int	word_n;
  int	i;
  int	j;

  if (wordtab == NULL)
    return (NULL);
  if (!(string = malloc(sizeof(char) * (get_string_len(wordtab)))))
  {
    fprintf(stderr, "%s\n", "Error malloc\n");
    return (NULL);
  }
  j = 0;
  word_n = 0;
  while (wordtab[word_n])
  {
    i = 0;
    while (wordtab[word_n][i] != '\0')
      string[j++] = wordtab[word_n][i++];
    string[j++] = ' ';
    ++word_n;
  }
  string[j] = '\0';
  return (string);
}

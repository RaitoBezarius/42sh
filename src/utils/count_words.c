/*
** count_words.c for test in /home/bebe-b_h/rendu/42sh
** 
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.net>
** 
** Started on  Mon May 11 22:26:22 2015 BEBE-BELL Hendy-Wilson
** Last update Mon May 11 22:26:41 2015 BEBE-BELL Hendy-Wilson
*/

#include <unistd.h>

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

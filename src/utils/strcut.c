/*
** strcut.c for 42sh in /home/bebe-b_h/projects/42sh
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri May 22 16:33:28 2015 BEBE-BELL Hendy-Wilson
** Last update Thu Jun 04 13:39:15 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <stdio.h>

#include "utils/strcut.h"

/*
** Fonction sur laquelle repose tout le programme
** DO NOT DELETE ! NE PAS SUPPRIMER ! PAREIL DANS UNE AUTRE LANGUE !
*/
int is_blank(char c)
{
  return (c == ' ' || c == '\t');
}

static t_strip_location count_stripped(const char *str, const int s_idx,
				       const int e_idx)
{
  t_strip_location location;

  location.start_index = s_idx;
  while (location.start_index < e_idx && is_blank(str[location.start_index]))
    ++location.start_index;
  location.end_index = e_idx;
  while (location.end_index > s_idx && is_blank(str[location.end_index]))
    --location.end_index;
  return (location);
}

/** TODO CRITICAL: strcut(line, 0, 1) will always return NULL
 **/
char			*strcut(const char *str, const int s_idx,
				const int e_idx)
{
  char			*tmp;
  int			index;
  t_strip_location	s_location;

  if (str == NULL || s_idx > e_idx)
    return (NULL);
  s_location = count_stripped(str, s_idx, e_idx);
  if ((s_location.end_index - s_location.start_index) < 0)
    return (NULL);
  tmp = malloc(sizeof(char) * (s_location.end_index - s_location.start_index
			       + 2));
  if (tmp == NULL)
  {
    fprintf(stderr, "Error malloc\n");
    return (NULL);
  }
  index = 0;
  while (s_location.start_index <= s_location.end_index)
  {
    tmp[index] = str[s_location.start_index];
    ++s_location.start_index;
    ++index;
  }
  tmp[index] = '\0';
  return (tmp);
}

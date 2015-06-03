/*
** strcut.c for 42sh in /home/bebe-b_h/projects/42sh
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri May 22 16:33:28 2015 BEBE-BELL Hendy-Wilson
** Last update Fri May 22 16:33:52 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <stdio.h>

#include "utils/strcut.h"

/*
** Fonction sur laquelle repose tout le programme
** DO NOT DELETE ! NE PAS SUPPRIMER ! LA MEME DANS UNE AUTRE LANGUE !
*/
int isblank(char c)
{
	return c == ' ';
}

t_strip_location count_stripped(const char	*str, const int s_idx, const int e_idx)
{
	t_strip_location location;

	location.start_index = s_idx;
	while (location.start_index < e_idx && isblank(str[location.start_index]))
		++location.start_index;
	location.end_index = e_idx;
	while (location.end_index > s_idx && isblank(str[location.end_index]))
		--location.end_index;
	return location;
}

char	*strcut(const char *str, const int s_idx, const int e_idx)
{
  char	*tmp;
  int	location;
	int index;
	t_strip_location s_location;

  if (str == NULL || s_idx >= e_idx)
    return (NULL);
	
	s_location = count_stripped(str, s_idx, e_idx);

	if ((s_location.end_index - s_location.start_index) <= 0)
		return (NULL);

  tmp = malloc(sizeof(char) * (s_location.end_index - s_location.start_index) + 2);
  if (tmp == NULL)
  {
    fprintf(stderr, "Error malloc\n");
    return (NULL);
  }

  location = s_location.start_index;
	index = 0;

	while (location <= s_location.end_index)
	{
		tmp[index] = str[location];
		location++;
		index++;
	}

  tmp[index] = '\0';
  return (tmp);
}

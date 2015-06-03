/*
** main.c for test in /home/bebe-b_h/rendu/42sh/src/builtin
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 17:41:31 2015 BEBE-BELL Hendy-Wilson
** Last update Sun May 24 17:43:43 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <stdio.h>

#include "get_next_line.h"

int	echo(char *line);

int	main(void)
{
  char	*str;
  printf("Input something : ");
  fflush(stdout);
  str = get_next_line(0);
  echo(str);
  return (0);
}

/*
** main.c for 42sh in /home/bebe-b_h/projects/42sh/src
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri Jun 05 07:40:53 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 07:53:22 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/get_next_line.h"
#include "execution/execute_ast.h"

int	main(void)
{
  char	*line;
  int	status_code;

  while (1)
  {
    printf("> ");
    fflush(stdout);
    line = get_next_line(0);
    if (strcmp(line, "exit") == 0 || !line)
    {
      free(line);
      return (0);
    }
    if (strcmp(line, "") == 0)
    {
      free(line);
      continue;
    }
    status_code = execute_line(line);
    free(line);
    if (status_code != 0)
      printf("Returned %d.\n", status_code);
  }
  return (0);
}

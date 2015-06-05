/*
** echo.c for 42sh in /home/bebe-b_h/projects/42sh/src/builtin
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Wed Jun 03 21:26:30 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:26:46 2015 BEBE-BELL Hendy-Wilson
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "builtin/echo.h"
#include "utils/string_utils.h"

int	echo(t_node_command *node)
{
  char	**args;
  int	opt_n;
  int	i;

  args = node->argv;
  opt_n = STREQ(args[1], "-n") ? 1 : 0;
  i = opt_n ? 2 : 1;
  while (args[i])
  {
    if (i > opt_n + 1)
      printf(" ");
    printf("%s", args[i]);
    ++i;
  }
  if (!opt_n)
    printf("\n");
  else
    fflush(stdout);
  return (0);
}

/*
** echo.c for 42sh in /home/bebe-b_h/projects/42sh/src/builtin
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Wed Jun 03 21:26:30 2015 BEBE-BELL Hendy-Wilson
** Last update Wed Jun 03 21:58:44 2015 BEBE-BELL Hendy-Wilson
*/

#include "string_utils.h"

int	echo(char **args)
{
  int	opt_n;
  int	i;

  opt_n = STREQ(args[0], "-n") ? 1 : 0;
  i = opt_n ? 1 : 0;
  while (args[i])
  {
    if (i > opt_n + 1)
      my_putchar(FD_OUT, ' ');
    my_putstr(FD_OUT, args[i]);
    ++i;
  }
  if (!opt_n)
    my_putchar(FD_OUT, '\n');
  return (0);
}

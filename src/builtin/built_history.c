/*
** built_history.c for 42sh in /home/meuric_a/42sh/src/builtin
** 
** Made by Alban Meurice
** Login   <meuric_a@epitech.net>
** 
** Started on  Thu May 21 16:55:37 2015 Alban Meurice
** Last update Fri May 22 15:29:40 2015 Alban Meurice
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"
#include "get_next_line.h"

int	built_history(char **line_cmd, char ***env)
{
  char	*str;
  int	fd;

  str = NULL;
  fd = 0;
  if (my_strcmp(line_cmd[0], "history") == 0)
    {
      if ((fd = open(my_getenv("PATH_HISTORY", (*env)), O_RDONLY)) == -1)
	return (-1);
      while ((str = get_next_line(fd)) != NULL)
	{
	  my_putstr(str);
	  my_putchar('\n');
	}
      return (0);
    }
  return (1);
}

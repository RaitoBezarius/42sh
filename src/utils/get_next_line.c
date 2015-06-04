/*
** get_next_line.c for get_next_line in /home/bebe-b_h/projects/tmp
** 
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.net>
** 
** Started on  Thu May  7 18:59:51 2015 BEBE-BELL Hendy-Wilson
** Last update Wed Jun 03 20:33:03 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <unistd.h>

#include "utils.h"
#include "get_next_line.h"

static size_t	my_strclen(const char *str, const char c)
{
  size_t	i;

  i = 0;
  if (str)
    while (str[i] && str[i] != c)
      ++i;
  return (i);
}

static char	*my_strcpy_c(char *to, char *from, const char c)
{
  size_t	i;

  i = 0;
  while (from[i] && from[i] != c)
    {
      to[i] = from[i];
      ++i;
    }
  to[i] = '\0';
  return (to);
}

static char	*my_realloc(char *str, const int size)
{
  char		*tmp;
  size_t	i;

  if (!(tmp = calloc(size, sizeof(char))))
    {
      write(2, ERR_ALLOC, my_strclen(ERR_ALLOC, '\0'));
      if (str)
	free(str);
      return (NULL);
    }
  i = 0;
  if (str)
    {
      while (str[i])
	{
	  tmp[i] = str[i];
	  ++i;
	}
      free(str);
    }
  tmp[i] = '\0';
  return (tmp);
}

static int	add_remain(char **str, char *remain)
{
  if (!remain[0])
    return (0);
  if (!(*str = malloc(sizeof(char) * (my_strclen(remain, '\n') + 1))))
    {
      write(2, ERR_ALLOC, my_strclen(ERR_ALLOC, '\0'));
      return (1);
    }
  my_strcpy_c(*str, remain, '\n');
  if (my_strclen(remain, '\n') != my_strclen(remain, '\0'))
    {
      my_strcpy_c(remain, &remain[my_strclen(remain, '\n') + 1], '\0');
      return (1);
    }
  remain[0] = '\0';
  return (0);
}

char		*get_next_line(const int fd)
{
  static char	remain[READ_SIZE + 1];
  char		buff[READ_SIZE + 1];
  char		*str;
  int		ret;
  int		loop;

  str = NULL;
  if (add_remain(&str, remain))
    return (str);
  loop = 1;
  buff[0] = '\0';
  while (loop == 1 && (ret = read(fd, buff, READ_SIZE)) > 0)
    {
      if (buff[0] == '\0')
	return (NULL);
      buff[ret] = '\0';
      if (!(str = my_realloc(str, my_strclen(str, '\0') + ret + 1)))
	return (NULL);
      my_strcpy_c(&str[my_strclen(str, '\0')], buff, '\n');
      loop = (my_strclen(buff, '\n') == my_strclen(buff, '\0'));
    }
  if (my_strclen(buff, '\n') != my_strclen(buff, '\0'))
    my_strcpy_c(remain, &buff[my_strclen(buff, '\n') + 1], '\0');
  return (str);
}

/*
** built_cd.c for Minishell1 in /home/meuric_a/Project/Minishell1/V5.0/src
** 
** Made by alban meurice
** Login   <meuric_a@epitech.net>
** 
** Started on  Wed Jan 28 17:39:56 2015 alban meurice
** Last update Thu May 21 16:55:24 2015 Alban Meurice
*/

#include <unistd.h>
#include <errno.h>
#include "utils.h"

int	built_cd(char **line_cmd, char ***env)
{
  if (my_strcmp(line_cmd[0], "cd") == 0)
    {
      if (line_cmd[1] != NULL)
	{
	  if (line_cmd[1][0] != '-')
	    {
	      if (get_pwd(env) == -1)
		return (-1);
	      if (chdir(line_cmd[1]) == -1)
		return (-1);
	    }
	  else
	    if (cd_back(env) == -1)
	      return (-1);
	  return (0);
	}
      if (line_cmd[1] == NULL)
	{
	  if (simple_cd(env) == -1)
	    return (-1);
	  return (0);
	}
    }
  return (1);
}

int	cd_back(char ***env)
{
  char	*str;

  str = NULL;
  if ((str = my_getenv("OLDPWD", *env)) == NULL)
    return (-1);
  if (get_pwd(env) == -1)
    return (-1);
  if (chdir(str) == -1)
    return (-1);
  return (0);
}

int	simple_cd(char ***env)
{
  char	*str;

  str = NULL;
  if ((str = my_getenv("HOME", *env)) == NULL)
    return (-1);
  my_putstr(str);
  if (get_pwd(env) == -1)
    return (-1);
  if (chdir(str) == -1)
    return (-1);
  return (0);
}

int	get_pwd(char ***env)
{
  char	*str;
  int	size;

  str = NULL;
  errno = 0;
  size = 0;
  while (((str = getcwd(str, size)) == NULL) && errno != 0)
    size = size + 1;
  if ((size = search_var("OLDPWD", (*env))) == -1)
    return (-1);
  if (((*env) = supr_line_tab((*env), size)) == NULL)
    return (-1);
  if ((str = my_strcat("OLDPWD=", str)) == NULL)
    return (-1);
  if (((*env) = create_new_tab((*env), str)) == NULL)
    return (-1);
  return (0);
}

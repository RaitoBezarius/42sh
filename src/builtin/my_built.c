/*
** my_built.c for Minishell1 in /home/meuric_a/Project/Minishell1/V5.0/src
** 
** Made by alban meurice
** Login   <meuric_a@epitech.net>
** 
** Started on  Tue Jan 27 17:42:02 2015 alban meurice
** Last update Fri May 22 15:10:15 2015 Alban Meurice
*/

#include <stdlib.h>
#include "utils.h"

int	built_exit(char **line_cmd)
{
  if (my_strcmp(line_cmd[0], "exit") == 0)
    return (0);
  return (1);
}

int	built_env(char **line_cmd, char **env)
{
  if (my_strcmp(line_cmd[0], "env") == 0)
    {
      show_tab(env);
      return (0);
    }
  return (1);
}

int	built_setenv(char **line_cmd, char ***env)
{
  char	*str;

  str = NULL;
  if (my_strcmp(line_cmd[0], "setenv") == 0)
    {
      if ((line_cmd[1] && line_cmd[1] != NULL) &&
	  (line_cmd[2] && line_cmd[2] != NULL))
	{
	  if ((str = my_strdup(line_cmd[1])) == NULL)
	    return (-1);
	  if ((str = my_strcat(str, "=\0")) == NULL)
	    return (-1);
	  if ((str = my_strcat(str, line_cmd[2])) == NULL)
	    return (-1);
	  if (((*env) = create_new_tab((*env), str)) == NULL)
	    return (-1);
	  return (0);
	}      
    }
  return (1);
}

int	built_unsetenv(char **line_cmd, char ***env)
{
  int	nb;

  nb = 0;
  if (my_strcmp(line_cmd[0], "unsetenv") == 0)
    {
      if (line_cmd[1] && line_cmd[1] != NULL)
	{
	  if ((nb = search_var(line_cmd[1], (*env))) == -1)
	    return (-1);
	  if (((*env) = supr_line_tab((*env), nb)) == NULL)
	    return (-1);
	  return (0);
	}
    }
  return (1);
}

int	my_built(char **line_cmd, char ***env)
{
  int	check;

  check = 0;
  if (built_exit(line_cmd) == 0)
    return (1);
  if ((check = built_cd(line_cmd, env)) == 0)
    return (0);
  if (check == -1)
    return (-1);
  if (built_echo(line_cmd) == 0)
    return (0);
  if (built_env(line_cmd, *env) == 0)
    return (0);
  if ((check = built_setenv(line_cmd, env)) == 0)
    return (0);
  if (check == -1)
    return (-1);
  if ((check = built_unsetenv(line_cmd, env)) == 0)
    return (0);
  if (check == -1)
    return (-1);
  if ((check = built_history(line_cmd, env)) == 0)
    return (0);
  if (check == -1)
    return (-1);
  return (2);
}

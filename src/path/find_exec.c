/*
** find_exec.c for 42sh in /home/bebe-b_h/projects/42sh/src/path
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri Jun 05 00:29:37 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:30:42 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "env.h"
#include "env_utils.h"
#include "utils.h"

static int	end_with_slash(const char *str)
{
  int		i;

  i = 0;
  while (str[i])
    ++i;
  if (str[i - 1] == '/')
    return (1);
  return (0);
}

/*
** TODO: Add default path if no env variable PATH exist
*/
static char	**gen_path_array(const char *name)
{
  char		**tab;
  t_env		*env_path;
  int		i;

  env_path = get_env("PATH");
  if (!env_path)
  {
    fprintf(stderr, "No path variable\n");
    return (NULL);
  }
  tab = str_to_wordtab(env_path->value, ':');
  if (!tab)
    return (NULL);
  i = 0;
  while (tab[i] != NULL)
  {
    if (!end_with_slash(tab[i]))
    {
      tab[i] = realloc(tab[i], sizeof(char) * (strlen(tab[i]) + 2));
      strcat(tab[i], "/");
    }
    tab[i] = realloc(tab[i],
		     sizeof(char) * (strlen(tab[i]) + strlen(name) + 1));
    strcat(tab[i], name);
    ++i;
  }
  return (tab);
}

static char	*check_cwd_file(char *file)
{
  if (access(file, F_OK) == 0)
    return (file);
  fprintf(stderr, "%s: command not found\n", file);
  return (NULL);
}

/*
** TODO: Add current working directory if ./
*/
char	*find_exec(char *name)
{
  char	**path_tab;
  char	*exec_path;
  int	i;

  if (strncmp(name, "./", 2) == 0)
    return (check_cwd_file(name));
  path_tab = gen_path_array(name);
  if (path_tab == NULL)
    return (NULL);
  i = 0;
  while (path_tab[i])
  {
    if (access(path_tab[i], F_OK) == 0)
    {
      exec_path = strdup(path_tab[i]);
      free_wordtab(path_tab);
      return (exec_path);
    }
    ++i;
  }
  fprintf(stderr, "%s: command not found\n", name);
  return (NULL);
}

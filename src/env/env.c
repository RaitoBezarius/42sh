/*
** env.c for 42sh in /home/bebe-b_h/rendu/42sh/src/env
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 04:56:04 2015 BEBE-BELL Hendy-Wilson
** Last update Sun May 24 16:23:04 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "env.h"
#include "env_utils.h"

t_env	*g_env_list = NULL;

/*
** Check if $name content is a valid envrionment variable name
*/
static int	check_name(const char *name)
{
 if (!IS_ALPHA(name[0]))
  {
    fprintf(stderr, "setenv: Variable name must begin with a letter.\n");
    return (-1);
  }
  if (!is_alphanum(name))
  {
    fprintf(stderr, "setenv: Variable name must be only alphanumeric.\n");
    return (-1);
  }
  return (0);
}

/*
** set an environment variable
** if name is NULL show environment var list
** if name is valid but wordlist is null:
**	delete var content
*/
int	my_setenv(const char *name, const char *value)
{
  t_env	*tmp;

  if (name == NULL)
    return (my_printenv(NULL));
  if (check_name(name) == -1)
    return (-1);
  tmp = get_env(name);
  if (tmp == NULL)
  {
    tmp = create_env_var(name);
    if (tmp == NULL)
      return (-1);
  }
  if (tmp->value)
    free(tmp->value);
  if (value == NULL || value[0] == '\0')
    tmp->value = NULL;
  else
    tmp->value = strdup(value);
  return (0);
}

/*
** Delete the environment variables which are listed in name_list
*/
int	my_unsetenv(const char **name_list)
{
  t_env	*tmp;
  t_env	*to_del;

  if (name_list == NULL || g_env_list == NULL)
    return (0);
  tmp = g_env_list;
  while (tmp != NULL && is_in_tab(tmp->name, name_list))
  {
    g_env_list = tmp->next;
    free(tmp);
    tmp = g_env_list;
  }
  if (tmp != NULL)
  {
    while (tmp->next != NULL)
    {
      if (is_in_tab(tmp->next, name_list))
      {
	to_del = tmp->next;
	tmp->next = tmp->next->next;
	free(to_del);
      }
      tmp = tmp->next;
    }
  }
  return (0);
}

int	my_printenv(const char *name)
{
  t_env	*tmp;

  tmp = get_env(name);
  if (tmp != NULL)
  {
    if (tmp->value  == NULL)
      printf("\n");
    else
      printf("%s\n", tmp->value);
  }
  else
  {
    tmp = g_env_list;
    while (tmp != NULL)
    {
      printf("%s=%s\n", tmp->name, tmp->value);
      tmp = tmp->next;
    }
  }
  return (0);
}

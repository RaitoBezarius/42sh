/*
** env_utils.c for 42sh in /home/bebe-b_h/rendu/42sh/src/env
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 05:36:19 2015 BEBE-BELL Hendy-Wilson
** Last update Sun May 24 15:55:46 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "env.h"
#include "env_utils.h"

/*
** Retrieve the environment variable which name is $name
*/
t_env	*get_env(const char *name)
{
  t_env	*tmp;

  tmp = g_env_list;
  while (tmp != NULL)
  {
    if (STREQ(name, tmp->name))
      return (tmp);
    tmp = tmp->next;
  }
  return (tmp);
}

/*
** Create an environment variable $name without a value and add it
** at the end of the global var g_env_list.
*/
t_env	*create_env_var(const char *name)
{
  t_env	*node;
  t_env	*tmp;

  if (!(node = malloc(sizeof(t_env))))
  {
    fprintf(stderr, "%s\n", "Error alloc\n");
    return (NULL);
  }
  node->name = strdup(name);
  node->value = NULL;
  node->next = NULL;
  tmp = g_env_list;
  if (tmp == NULL)
    g_env_list = node;
  else
  {
    while (tmp->next != NULL)
      tmp = tmp->next;
    tmp->next = node;
  }
  return (node);
}

/*
** alias_utils.c for 42sh in /home/bebe-b_h/rendu/42sh/src/alias
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 05:36:19 2015 BEBE-BELL Hendy-Wilson
** Last update Sun May 24 15:51:17 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "alias.h"
#include "alias_utils.h"

t_alias		*get_alias(const char *name)
{
  t_alias	*tmp;

  tmp = g_alias_list;
  while (tmp != NULL)
  {
    if (STREQ(name, tmp->name))
      return (tmp);
    tmp = tmp->next;
  }
  return (tmp);
}

t_alias		*create_alias(const char *name)
{
  t_alias	*node;
  t_alias	*tmp;

  if (!(node = malloc(sizeof(t_alias))))
  {
    fprintf(stderr, "%s\n", "Error alloc\n");
    return (NULL);
  }
  node->name = strdup(name);
  node->value = NULL;
  node->next = NULL;
  tmp = g_alias_list;
  if (tmp == NULL)
    g_alias_list = node;
  else
  {
    while (tmp->next != NULL)
      tmp = tmp->next;
    tmp->next = node;
  }
  return (node);
}

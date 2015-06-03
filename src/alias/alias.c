/*
** alias.c for 42sh in /home/bebe-b_h/rendu/42sh/src/alias
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 04:56:04 2015 BEBE-BELL Hendy-Wilson
** Last update Sun May 24 16:14:09 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils/wordtab_to_str.h"
#include "utils/string_utils.h"
#include "alias.h"
#include "alias_utils.h"

t_alias	*g_alias_list = NULL;

/*
** Print an alias if $name is found in the alias_list
** if name is NULL, print the alias_list
*/
static int	print_alias(const char *name)
{
  t_alias	*tmp;

  if (name != NULL)
  {
    tmp = get_alias(name);
    if (tmp == NULL)
      return (0);
    if (tmp->value  == NULL)
      printf("\n");
    else
      printf("%s\n", tmp->value);
  }
  else
  {
    tmp = g_alias_list;
    while (tmp != NULL)
    {
      printf("%s\t(%s)\n", tmp->name, tmp->value);
      tmp = tmp->next;
    }
  }
  return (0);
}

/*
** Check if the name when calling alias is valid
*/
static int	check_name(const char *name)
{
  if (STREQ(name, "alias") || STREQ(name, "unalias"))
  {
    fprintf(stderr, "%s: Too dangerous to alias that.\n", name);
    return (-1);
  }
  return (0);
}

/*
** If $name is NULL / $wordlist is NULL, print the list of alias / the alias
** which name is equal to $name
** If both params are valid, create (or replace) the alias.
*/
int		alias(const char *name, const char **wordlist)
{
  t_alias	*tmp;

  if (name == NULL || wordlist == NULL)
    return (print_alias(name));
  if (check_name(name) == -1)
    return (-1);
  tmp = get_alias(name);
  if (tmp == NULL)
  {
    tmp = create_alias(name);
    if (tmp == NULL)
      return (-1);
  }
  if (tmp->value)
    free(tmp->value);
  if (wordlist == NULL || wordlist[0] == NULL)
    tmp->value = NULL;
  else
    tmp->value = wordtab_to_str(wordlist);
  return (0);
}

/*
** Delete the aliases which names are in $name_list
*/
int		unalias(const char **name_list)
{
  t_alias	*tmp;
  t_alias	*to_del;

  if (name_list == NULL || g_alias_list == NULL)
    return (0);
  tmp = g_alias_list;
  while (tmp != NULL && is_in_tab(tmp->name, name_list))
  {
    g_alias_list = tmp->next;
    free(tmp);
    tmp = g_alias_list;
  }
  if (tmp != NULL)
  {
    while (tmp->next != NULL)
    {
      if (is_in_tab(tmp->next->name, name_list))
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

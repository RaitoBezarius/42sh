/*
** alias.h for 42sh in /home/bebe-b_h/rendu/42sh/src/alias
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 14:40:43 2015 BEBE-BELL Hendy-Wilson
** Last update Sun May 24 16:28:10 2015 BEBE-BELL Hendy-Wilson
*/

#ifndef ALIAS_H_
# define ALIAS_H_

typedef struct	s_alias
{
  char		*name;
  char		*value;
  struct s_alias		*next;
}		t_alias;

int		alias(const char *name, const char **value_list);
int		unalias(const char **name_list);

#define STREQ(a, b) strcmp(a, b) == 0

extern t_alias	*g_alias_list;

#endif /* !ALIAS_H_ */

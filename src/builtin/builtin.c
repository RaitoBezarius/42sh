/*
** builtin.c for 42sh in /home/bebe-b_h/rendu/42sh/src/builtin
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 20:18:05 2015 BEBE-BELL Hendy-Wilson
** Last update Wed Jun 03 13:32:41 2015 BEBE-BELL Hendy-Wilson
*/

#include "builtins.h"

/* FIXME: REMOVE BUILTINS THAT ARE NOT IN THE PROGRAM ! */
static t_builtin	g_builtins[] = {
  {"cd", cd},
  {"setenv", my_setenv},
  {"unsetenv", my_unsetenv},
  {"printenv", my_printenv},
  {"alias", alias},
  {"unalias", unalias},
  {"history", history},
  {"echo", echo},
  {"exit", my_exit}
}

int	(is)

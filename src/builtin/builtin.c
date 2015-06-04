/*
** builtin.c for 42sh in /home/bebe-b_h/rendu/42sh/src/builtin
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 20:18:05 2015 BEBE-BELL Hendy-Wilson
** Last update Wed Jun 03 13:32:41 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>
#include <string.h>

#include "builtins.h"
#include "builtin/echo.h"

t_builtin	g_builtins[] = {
  {"echo", echo},
	{NULL, NULL}
};

t_builtin_ptr	get_builtin(char	*name)
{
	int index;
	
	index = 0;
	while (g_builtins[index].name != NULL)
	{
		if (strcmp(g_builtins[index].name, name) == 0)
			return g_builtins[index].func;
	}

	return NULL;
}

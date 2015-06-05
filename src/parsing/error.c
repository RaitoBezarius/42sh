/*
** error.c for 42sh in /home/bebe-b_h/projects/42sh/src/parsing
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri Jun 05 08:34:06 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:34:22 2015 BEBE-BELL Hendy-Wilson
*/

#include "parsing/error.h"

#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>

void	set_error(t_parse_state	*state, const char *format, ...)
{
  char buffer[MAX_ERROR_BUFFER];
  va_list args;

  state->bit_ok = FALSE;
  va_start(args, format);
  vsprintf(buffer, format, args);
  fprintf(stderr, "%s", buffer);
  va_end(args);
}

void	panic(t_parse_state *state)
{
  free(state);
}

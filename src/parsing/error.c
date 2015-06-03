#include "parsing/error.h"

#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>

void	set_error(t_parse_state	*state, const char	*format, ...)
{
	char buffer[MAX_ERROR_BUFFER];
	va_list args;

	state->bit_ok = FALSE;
	va_start(args, format);
	vsprintf(buffer, format, args);
	fprintf(stderr, buffer);
	va_end(args);
}

void	panic(t_parse_state	*state)
{
	free(state);
}

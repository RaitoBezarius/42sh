#include "parsing/state.h"

#include "definitions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


t_parse_state	*init_parse_state(char	*line)
{
	t_parse_state	*state;

	state = (t_parse_state *)malloc(sizeof(t_parse_state));
	if (!state)
	{
		fprintf(stderr, "Allocation failed!");
		return NULL;
	}

	state->line = line;
	state->line_length = strlen(line);
	state->current_index = 0;
	state->start_index = 0;
	state->bit_ok = TRUE;

	return state;
}

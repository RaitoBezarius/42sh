#include "parsing/state.h"

#include <stdlib.h>
#include <string.h>

s_parse_state	*initialize_parse_state(char	*line)
{
	s_parse_state	*state;

	state = (s_parse_state *)malloc(sizeof(s_parse_state));
	if (!state)
	{
		fprintf(stderr, "Allocation failed!");
		return NULL;
	}

	state->line = line;
	state->line_length = strlen(line);
	state->current_index = 0;
	state->start_index = 0;

	return state;
}

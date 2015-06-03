#include "parsing/matchers/execution_parallel.h"
#include "parsing/ast.h"
#include "parsing/token_matchers.h"

#include "definitions.h"


int match_token_smcln(t_parse_state	*state)
{
	if (state->line[state->current_index] == ';')
		return TK_SMCLN;
	return FALSE;
}

void	dispatch_token_smcln(t_parse_state	*state, t_linked_list	**current)
{
	state->current_index++;
	push_to_linked_list((*current), create_token(TK_SMCLN), ITEM_TOKEN);
}

int match_token_esperluette(t_parse_state	*state)
{
	if (state->line[state->current_index] == '&' && state->line[state->current_index + 1] != '&')
		return TK_ESPERLUETTE;
	return FALSE;
}

void	dispatch_token_esperluette(t_parse_state	*state, t_linked_list	**current)
{
	state->current_index++;
	push_to_linked_list((*current), create_token(TK_ESPERLUETTE), ITEM_TOKEN);
}

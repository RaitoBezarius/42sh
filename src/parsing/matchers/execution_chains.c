#include "parsing/matchers/execution_chains.h"
#include "parsing/ast.h"
#include "parsing/token_matchers.h"

#include "definitions.h"

int match_token_and(t_parse_state	*state)
{
	if (state->line[state->current_index] == '&' && state->line[state->current_index + 1] == '&')
		return TK_AND;
	return FALSE;
}

int	match_token_or(t_parse_state	*state)
{
	if (state->line[state->current_index] == '|' && state->line[state->current_index + 1] == '|')
		return TK_OR;
	return FALSE;
}

void	dispatch_token_and(t_parse_state	*state, t_linked_list	**current)
{
	state->current_index += 2;
	push_to_linked_list((*current), create_token(TK_AND), ITEM_TOKEN);
}

void	dispatch_token_or(t_parse_state	*state, t_linked_list	**current)
{
	state->current_index += 2;
	push_to_linked_list((*current), create_token(TK_OR), ITEM_TOKEN);
}

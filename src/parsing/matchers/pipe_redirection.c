#include "parsing/matchers/pipe_redirection.h"
#include "parsing/redirection_matchers.h"
#include "parsing/parse.h"
#include "parsing/ast.h"

#include "definitions.h"

int	match_redirect_pipe(t_parse_state	*state)
{
	if (state->line[state->current_index] == '|' && state->line[state->current_index + 1] != '|')
		return REDIR_PIPE;
	return FALSE;
}

void	dispatch_pipe_redirection(t_parse_state	*state, t_linked_list	**current)
{
	t_redirection	*redirection;

	state->current_index++;
	skipPast(state, ' ');
	redirection = create_redirection();
	redirection->type = REDIR_PIPE;
	push_to_linked_list((*current), redirection, ITEM_REDIRECTION, redirection_freer);
	(*current) = (*current)->next;
}

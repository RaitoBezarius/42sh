#include "parsing/command_matcher.h"
#include "parsing/redirection_matchers.h"
#include "parsing/token_matchers.h"

#include "parsing/ast.h"
#include "parsing/error.h"

#include "utils/strcut.h"

void	match_command(t_parse_state	*state, t_linked_list	**current)
{
	t_node_command	*command;
	char	*exe_line;

	while (state->line[state->current_index] == ' ')
		state->current_index++;
	state->start_index = state->current_index;
	while (state->current_index < state->line_length 
			&& !(is_redirection(state) || is_token(state)))
		state->current_index++;
	exe_line = strcut(state->line, state->start_index, state->current_index - 1);
	command = create_node();
	command->executable = exe_line;
	push_to_linked_list((*current), command, ITEM_COMMAND);
	(*current) = (*current)->next;
}

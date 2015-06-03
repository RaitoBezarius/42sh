#include "parsing/command_matcher.h"
#include "parsing/error.h"

void	match_command(t_parse_state	*state, t_linked_list	**current)
{
	t_node_command	*command;

	while (state->line[state->current_index] == ' ')
		state->current_index++;
	state->start_index = state->current_index;
	while (state->current_index < state->line_length 
			&& !(is_redirection(state) || is_token(state)))
		state->current_index++;
	char	*exe_line = strcut(state->line, state->start_index, state->current_index - 1);
	command = create_node();
	command->executable = exe_line;
	(*current)->item = command;
	(*current)->type = ITEM_COMMAND;
	(*current)->next = create_linked_list();
	(*current)->next->prev = (*current);
	(*current) = (*current)->next;
}

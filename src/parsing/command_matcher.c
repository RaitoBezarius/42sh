#include "parsing/command_matcher.h"
#include "parsing/redirection_matchers.h"
#include "parsing/token_matchers.h"

#include "parsing/ast.h"
#include "parsing/parse.h"
#include "parsing/error.h"

#include "utils/strcut.h"

#include <stdlib.h>

void	command_freer(void	*item)
{
	t_node_command	*cmd;

	cmd = (t_node_command	*)item;
	free(cmd->executable);
	cmd->executable = NULL;
	if (cmd->argv)
	{
		free(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->out)
	{
		redirection_freer(cmd->out);
		cmd->out = NULL;
	}
	if (cmd->in)
	{
		redirection_freer(cmd->in);
		cmd->in = NULL;
	}

	free(cmd);
}

void	match_command(t_parse_state	*state, t_linked_list	**current)
{
	t_node_command	*command;
	char	*exe_line;
	
	skipPast(state, ' ');
	state->start_index = state->current_index;
	while (state->current_index < state->line_length 
			&& !(is_redirection(state) || is_token(state)))
		state->current_index++;
	skipPast(state, ' ');
	state->current_index--;
	exe_line = strcut(state->line, state->start_index, state->current_index);
	command = create_node();
	command->executable = exe_line;
	push_to_linked_list((*current), command, ITEM_COMMAND, command_freer);
	(*current) = (*current)->next;
	state->current_index++;
}

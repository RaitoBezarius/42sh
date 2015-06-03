#include "parsing/parse.h"
#include "parsing/state.h"
#include "parsing/error.h"

#include "parsing/redirection_matchers.h"
#include "parsing/token_matchers.h"
#include "parsing/command_matcher.h"
#include "parsing/parse_passes.h"

#include <string.h>

t_ast_list	*parse_line(char	*line)
{
	t_linked_list	*nodes_list;
	t_ast_list	*list_ast;
	int	index;

	nodes_list = form_initial_list(line);
	index = 0;

	while (index < N_PASSES)
	{
		if (!passes[index](nodes_list))
			return NULL;
	}

	list_ast = build_tree(nodes_list);
	if (!list_ast)
		return NULL;

	free_linked_list(nodes_list);
	return list_ast;
}

t_linked_list	*form_initial_list(char	*line)
{
	t_parse_state	*state;
	t_linked_list	*start;
	t_linked_list	*current;
	
	state = init_parse_state(line);
	start = create_linked_list();
	if (!state || !start)
		return NULL;
	current = start;
	while (state->current_index < state->line_length)
	{
		if (is_redirection(state))
			match_redirection(state, &current);
		else if (is_token(state))
			match_token(state, &current);
		else
			match_command(state, &current);
		if (!state->bit_ok)
		{
			panic(state);
			return NULL;
		}
	}
	return start;
}

t_ast_list	*build_tree(t_linked_list	*nodes_list)
{
	t_ast_list	*tree;
}

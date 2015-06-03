#include "parsing/parse.h"
#include "parsing/state.h"

#include <string.h>

t_ast	**parse_line(char	*line)
{
	t_linked_list	*nodes_list;
	t_ast	**list_ast;
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
	s_parse_state	*state;
	t_linked_list	*nodes;
	
	state = initialize_parse_state(line);
	nodes = create_linked_list();
	if (!state || !nodes)
		return NULL;
	while (state->current_index < state->line_length)
	{
		if (is_redirection(&state))
			match_redirection(&state, &nodes);
		else if (is_token(&state))
			match_token(&state, &nodes);
		else
			match_command(&state, &nodes);
	}
	return nodes;
}

t_ast	**build_tree(t_linked_list	*nodes_list)
{
	t_ast	**tree;
}

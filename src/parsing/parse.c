#include "parsing/parse.h"
#include "parsing/state.h"

#include <string.h>

t_ast	**parse_line(char	*line)
{
	linked_list	*nodes_list;
	t_ast	**list_ast;

	nodes_list = form_initial_list(line);
	if (!nodes_list || !relocate(nodes_list)
			|| !inject_redirection_into_nodes(nodes_list)
			|| !reorganize_pipes(nodes_list)
			|| !analyze_command_argv(nodes_list))
		return NULL;

	list_ast = build_tree(nodes_list);
	if (!list_ast)
		return NULL;

	free_linked_list(nodes_list);
	return list_ast;
}

linked_list	*form_initial_list(char	*line)
{
	s_parse_state	*state;
	linked_list	*nodes;
	
	state = initialize_parse_state(line);
	nodes = init_linked_list();
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

int relocate(linked_list	*nodes_list)
{
	linked_list	*start;

	start = nodes_list;
	while (nodes_list)
	{
		if (nodes_list->type == ITEM_REDIRECTION && 
				!(nodes_list->prev && nodes_list->prev->type == ITEM_COMMAND))
		{
			start = nodes_list;
			while ((nodes_list = nodes_list->next) 
					&& (nodes_list->type != ITEM_COMMAND 
						|| nodes_list->type != ITEM_TOKEN));
			if (nodes_list->type != ITEM_COMMAND)
			{
				fprintf(stderr, "Syntax error, no command before / after redirection.");
				return FALSE;
			}
			else
				move_item_before(nodes_list, start); /** Move COMMAND before first REDIRECTION **/
		}

		nodes_list = nodes_list->next;
	}
	return TRUE;
}

int inject_redirection_into_nodes(linked_list	*nodes_list)
{
	t_node_command	*current_command;
	t_redirection	*current_redirection;
	
	current_redirection = NULL;
	current_command = (t_node_command *)nodes_list->item;
	while (nodes_list)
	{
		if (nodes_list->type == ITEM_REDIRECTION)
		{
			current_redirection = (t_redirection *)nodes_list->item;
			if (current_redirection->type != REDIR_PIPE)
			{
				if (current_redirection->way == INPUT)
					current_command->in = current_redirection;
				else
					current_command->out = current_redirection;
				remove_linked_item(nodes_list);
				continue;
			}
		}
		else if (nodes_list->type == ITEM_COMMAND)
			current_command = (t_node_command *)nodes_list->item;
		nodes_list = nodes_list->next;
	}
	return TRUE;
}

int	reorganize_pipes(linked_list	*nodes_list)
{
	stack	*pipes;
	int	*pipefd;
	
	pipes = create_stack();
	if (!pipes)
		return FALSE;
	if (pipe(pipefd) == -1)
		return FALSE;

	while (nodes_list = nodes_list->next)
	{
		if (nodes_list->type == ITEM_REDIRECTION)
		{

		}
	}
	return TRUE;
}

int analyze_command_argv(linked_lsit	*nodes_list)
{
	t_command_node	*command;

	command = NULL;
	while (nodes_list = nodes_list->next)
	{
		if (nodes_list->type == ITEM_COMMAND)
		{
			command = (t_command_node	*)nodes_list->item;
			command->argv = strtok(command->executable, " ");
			command->executable = command->argv[0];
			command->argv = &command->argv[1];
			/** TODO: Is there a memory leak somewhere that I can't see ? **/
		}
	}
	return TRUE;
}

t_ast	**build_tree(linked_list	*nodes_list)
{
	t_ast	**tree;
}

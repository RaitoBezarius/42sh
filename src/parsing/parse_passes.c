#include "parsing/parse_passes.h"

#include "definitions.h"

pass_function passes[] = {
	relocate,
	inject_redirection_into_nodes,
	reorganize_pipes,
	analyze_command_argv
};

int relocate(t_linked_list *nodes_list)
{
	t_linked_list *start;

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

int inject_redirection_into_nodes(t_linked_list *nodes_list)
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

int	reorganize_pipes(t_linked_list *nodes_list)
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

int analyze_command_argv(linked_list	*nodes_list)
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



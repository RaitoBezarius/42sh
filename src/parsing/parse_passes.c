#include "parsing/parse_passes.h"
#include "parsing/ast.h"
#include "parsing/redirection_matchers.h"

#include "utils/line_to_wordtab.h"

#include "definitions.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

pass_function passes[] = {
	relocate,
	/** TODO: It's quite tricky to make it work: inject_redirection_into_nodes, **/
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
			while (nodes_list 
					&& (nodes_list->type != ITEM_COMMAND 
						|| nodes_list->type != ITEM_TOKEN))
			{
				nodes_list = nodes_list->next;
			}
			if (!nodes_list || nodes_list->type != ITEM_COMMAND)
			{
				fprintf(stderr, "Syntax error, no command before / after redirection.\n");
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
	int	pipefd[2];
	
	if (pipe(pipefd) == -1)
		return FALSE;

	while ((nodes_list = nodes_list->next))
	{
		if (nodes_list->type == ITEM_REDIRECTION)
		{

		}
	}
	return TRUE;
}

int analyze_command_argv(t_linked_list	*nodes_list)
{
	t_node_command	*command;

	command = NULL;
	while (nodes_list)
	{
		if (nodes_list->type == ITEM_COMMAND)
		{
			command = (t_node_command	*)nodes_list->item;
			command->argv = line_to_wordtab(command->executable);
			/** TODO: Is there a memory leak somewhere that I can't see ? **/
		}

		nodes_list = nodes_list->next;
	}
	return TRUE;
}



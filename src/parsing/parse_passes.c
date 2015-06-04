#include "parsing/parse_passes.h"
#include "parsing/ast.h"
#include "parsing/redirection_matchers.h"
#include "parsing/token_matchers.h"
#include "parsing/parse_utils.h"
#include "parsing/syntax_checker.h"

#include "utils/line_to_wordtab.h"
#include "utils/command_type.h"

#include "execution/exec_functions.h"

#include "builtins.h"

#include "definitions.h"

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

pass_function passes[] = {
	relocate,
	check_syntax,
	inject_redirection_into_nodes,
	reorganize_pipes,
	analyze_command_argv
};

int relocate(t_linked_list **nodes_list)
{
	t_linked_list *start;
	t_linked_list	*future_next;
	t_redirection	*redir;

	start = (*nodes_list);
	while ((*nodes_list))
	{
		if ((*nodes_list)->type == ITEM_REDIRECTION
				&& !((*nodes_list)->prev && (*nodes_list)->prev->type == ITEM_COMMAND))
		{
			redir = (t_redirection	*)(*nodes_list)->item;
			if (redir->type != REDIR_PIPE)
			{
				start = (*nodes_list);
				while ((*nodes_list) 
						&& (*nodes_list)->type != ITEM_COMMAND 
							&& (*nodes_list)->type != ITEM_TOKEN)
				{
					(*nodes_list) = (*nodes_list)->next;
				}
				if (!(*nodes_list) || (*nodes_list)->type != ITEM_COMMAND)
				{
					fprintf(stderr, "Syntax error, no command before / after redirection.\n");
					return FALSE;
				}
				else
				{
					future_next = (*nodes_list)->prev;
					move_item_before((*nodes_list), start); /** Move COMMAND before first REDIRECTION **/
					start = (*nodes_list);
					(*nodes_list) = future_next;
				}
			}
		}
		else if ((*nodes_list)->type == ITEM_REDIRECTION)
		{
			while ((*nodes_list) && (*nodes_list)->type == ITEM_REDIRECTION)
				(*nodes_list) = (*nodes_list)->next;
		}
		
		if ((*nodes_list))
			(*nodes_list) = (*nodes_list)->next;
	}
	(*nodes_list) = start;
	return TRUE;
}

int inject_redirection_into_nodes(t_linked_list **nodes_list)
{
	t_node_command	*current_command;
	t_redirection	*current_redirection;
	t_linked_list	*start;
	t_linked_list	*prev;
	
	current_redirection = NULL;
	current_command = (t_node_command *)(*nodes_list)->item;
	start = (*nodes_list);
	while ((*nodes_list))
	{
		if ((*nodes_list)->type == ITEM_REDIRECTION)
		{
			current_redirection = (t_redirection *)(*nodes_list)->item;
			if (current_redirection->type != REDIR_PIPE)
			{
				if (current_redirection->way == INPUT)
					current_command->in = current_redirection;
				else
					current_command->out = current_redirection;
				prev = (*nodes_list)->prev;
				remove_linked_item((*nodes_list), FALSE);
				(*nodes_list) = prev;
				continue;
			}
		}
		else if ((*nodes_list)->type == ITEM_COMMAND)
			current_command = (t_node_command *)(*nodes_list)->item;
		(*nodes_list) = (*nodes_list)->next;
	}
	(*nodes_list) = start;
	return TRUE;
}

int	reorganize_pipes(t_linked_list **nodes_list)
{
	t_linked_list	*start;
	t_node_command	*left;
	t_node_command	*right;
	t_redirection	*r_pipe;
	
	start = (*nodes_list);
	while ((*nodes_list))
	{
		if ((*nodes_list)->type == ITEM_REDIRECTION)
		{
			r_pipe = (t_redirection	*)(*nodes_list)->item;
			if (r_pipe->type == REDIR_PIPE)
			{
				int pipefd[2];

				if (pipe(pipefd) == -1)
				{
					fprintf(stderr, "Failed to create a pipe: %s", strerror(errno));
					return FALSE;
				}

				left = (t_node_command	*)((*nodes_list)->prev->item);
				left->out = create_redirection();
				left->out->fd = pipefd[0];

				right = (t_node_command	*)((*nodes_list)->next->item);
				right->in = create_redirection();
				right->in->fd = pipefd[1];

				remove_linked_item((*nodes_list), TRUE);
				(*nodes_list) = start;
			}
		}
		(*nodes_list) = (*nodes_list)->next;
	}
	
	(*nodes_list) = start;
	return TRUE;
}

int analyze_command_argv(t_linked_list	**nodes_list)
{
	t_node_command	*command;
	t_linked_list	*start;

	command = NULL;
	start = (*nodes_list);
	while ((*nodes_list))
	{
		if ((*nodes_list)->type == ITEM_COMMAND)
		{
			command = (t_node_command	*)(*nodes_list)->item;

			if (is_alias(command->executable))
				command->execute = execute_alias;
			else if (is_builtin(command->executable))
				command->execute = get_builtin(command->executable);
			else
				command->execute = standard_execute;
			
			command->argv = line_to_wordtab(command->executable);
		}

		(*nodes_list) = (*nodes_list)->next;
	}
	(*nodes_list) = start;

	return TRUE;
}



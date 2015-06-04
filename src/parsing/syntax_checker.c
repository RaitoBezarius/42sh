#include "parsing/syntax_checker.h"

#include "parsing/parse_utils.h"
#include "parsing/ast.h"
#include "parsing/redirection_matchers.h"
#include "parsing/token_matchers.h"

#include <stdlib.h>
#include <stdio.h>

#include "definitions.h"

void	no_freer(void	*ptr)
{
	(void)ptr;
}

t_linked_list	*transform_syntax(t_linked_list	*nodes)
{
	t_redirection	*redirection;
	t_linked_list	*new_nodes;
	
	new_nodes = create_linked_list();
	while (nodes)
	{
		if (nodes->type == ITEM_REDIRECTION)
		{
			redirection = (t_redirection	*)nodes->item;
			if (redirection->type == REDIR_PIPE)
				push_to_linked_list(new_nodes, NULL, ITEM_PIPE, no_freer);
			else
				push_to_linked_list(new_nodes, redirection, ITEM_REDIRECTION, no_freer);
		}
		else if (nodes->type == ITEM_COMMAND)
			push_to_linked_list(new_nodes, nodes->item, ITEM_COMMAND, no_freer);
		else if (nodes->type == ITEM_TOKEN)
			push_to_linked_list(new_nodes, nodes->item, ITEM_TOKEN, no_freer);

		nodes = nodes->next;
	}

	while (new_nodes)
	{
		if (new_nodes->type == 0)
			remove_linked_item(new_nodes, FALSE);

		new_nodes = new_nodes->next;
	}

	return new_nodes;
}

int	check_syntax(t_linked_list	**nodes_list)
{
	t_linked_list	*new_list;
	int status;

	new_list = transform_syntax((*nodes_list));

	while (new_list)
	{
		status = expect_block(&new_list);
		if (status == FAILED)
			return FALSE;
		else if (status == FINISHED)
			return TRUE;
		else
		{
			status = expect_token(&new_list);
			if (status == FAILED)
				return FALSE;
			else if (status == FINISHED)
				return TRUE;
		}
	}

	free_linked_list(new_list);
	return TRUE;
}

int	expect_block(t_linked_list	**list)
{
	if (!expect(list, ITEM_COMMAND))
	{
		fprintf(stderr, "Syntax error, expected command.\n");
		return FAILED;
	}

	if (!(*list))
		return FINISHED;

	if (expect(list, ITEM_REDIRECTION))
	{
		expect(list, ITEM_REDIRECTION);

		if (!(*list))
			return FINISHED;

		if (expect(list, ITEM_REDIRECTION))
		{
			fprintf(stderr, "Syntax error, expected token or command, got redirection. You cannot do more than 2 redirections in a block!\n");
			return FAILED;
		}
	}
	return CONTINUE;
}

int expect_token(t_linked_list	**list)
{
	int tk_type;
	t_linked_list	*checkp;
	
	checkp = (*list);
	if (expect(list, ITEM_TOKEN))
	{
		tk_type = *((int*)checkp->item);
		if (tk_type != TK_ESPERLUETTE)
			return CONTINUE;
		else
			return (*list) ? expect_token(list) : FINISHED;
	}
	else if (expect(list, ITEM_PIPE))
		return CONTINUE;
	else
	{
		fprintf(stderr, "Expected either a token or a pipe, neither were found.\n");
		return FAILED;
	}
}

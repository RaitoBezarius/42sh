#include "parsing/ast.h"

#include "parsing/token_matchers.h"
#include "parsing/redirection_matchers.h"

#include "definitions.h"

#include <stdio.h>

t_ast	*create_ast()
{
	t_ast	*ast;
	
	ast = malloc(sizeof(t_ast));
	if (!ast)
	{
		fprintf(stderr, "Allocation failed!");
		return NULL;
	}
	ast->left = NULL;
	ast->right = NULL;
	ast->node = create_node();
	if (!ast->node)
	{
		free(ast);
		return NULL;
	}
	return ast;
}

t_node_command	*create_node()
{
	t_node_command	*node;

	node = malloc(sizeof(t_node));
	node->executable = NULL;
	node->argv = NULL;
	node->out = NULL;
	node->in = NULL;
	node->flag_background = FALSE;
	if (!node)
	{
		fprintf(stderr, "Allocation failed!");
		return NULL;
	}
	return node;
}

t_redirection	*create_redirection()
{
	t_redirection	*redirection;

	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
	{
		fprintf(stderr, "Allocation failed!");
		return NULL;
	}
	redirection->type = 0;
	redirection->filename = NULL;
	redirection->fd = 0;
	return redirection;
}

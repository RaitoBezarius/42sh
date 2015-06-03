#include "parsing/ast.h"

#include "parsing/token_matchers.h"
#include "parsing/redirection_matchers.h"

#include "definitions.h"

#include <stdio.h>

t_grammar_definition grammar_definitions[] = {

	{ TK_AND, "And", match_token_and },

	{ TK_OR, "Or", match_token_or },

	{ TK_SMCLN, "Semicolon", match_token_semicolon },

	{ REDIR_STDIN, "Redirect stdin (<)", match_redir_stdin },

	{ REDIR_STDOUT_TRUNC, "Redirect stdout (>) by truncating the file", 
		match_redir_stdout },

	{ REDIR_STDIN_EOL, "Redirect stdin with a custom EOL (<<)", 
		match_redir_stdin_eol },

	{ REDIR_STDOUT_APP, "Redirect stdout (>>) by appending to file", 
		match_redir_stdout_app },

	{ REDIR_PIPE, "Redirect by piping left stdout to right stdin (|)", 
		match_redir_pipe }
};

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

#include "parsing/ast.h"

#include "parsing/token_matchers.h"
#include "parsing/redirection_matchers.h"

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
	ast->left = NULL;
	ast->right = NULL;
	ast->node = create_node();
	if (!ast)
	{
		fprintf(stderr, "Allocation failed!");
		return NULL;
	}
	return ast;
}

t_node	*create_node()
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = ND_NONE;
	node->data = NULL;
	if (!node)
	{
		fprintf(stderr, "Allocation failed!");
		return NULL;
	}
	return node;
}

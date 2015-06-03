#ifndef PARSE_H_DEFINED
#define PARSE_H_DEFINED

#include "parsing/ast.h"
#include "parsing/state.h"
#include "utils/linked_list.h"

/** parse_line returns a list of AST which can be safely executed. **/
t_ast_list	*parse_line(char	*line);

/** This is the initial pass, it forms a initial global AST by doing COMMAND [REDIRECTION] [REDIRECTION] [TOKEN COMMAND] ... **/
/** It will pay attention to delimitors like ", ' and other... **/
t_linked_list	*form_initial_list(char	*line);

/** This is the final pass, it builds a tree from tokens (on success, on fail, parallel execution)
 * Tokens are organized as: 
 *		- Simple & flag the previous command as "Run in background" mode.
 *		- AND is the left part of a binary tree
 *		- OR is the right part of a binary tree
 *		- Semicolon create a new AST
**/
t_ast_list	*build_tree(t_linked_list	*nodes_list);

void	skipPast(t_parse_state	*state, char character);
void	skipToNext(t_parse_state	*state, char character);

void	print_debug_list(t_linked_list	*nodes_list);
void	print_debug_node(t_linked_list	*node);

#endif

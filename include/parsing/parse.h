#ifndef PARSE_H_DEFINED
#define PARSE_H_DEFINED

#include "parsing/ast.h"
#include "utils/linked_list.h"

/** parse_line returns a list of AST which can be safely executed. **/
t_ast	**parse_line(char	*line);

/** This is the first pass, it forms a initial global AST by doing COMMAND [REDIRECTION] [REDIRECTION] [TOKEN COMMAND] ... **/
/** It will pay attention to delimitors like ", ' and other... **/
linked_list	*form_initial_list(char	*line);

/** This is the second pass, it will check the syntax and relocate pre-fix / post-fix elements.
 * Example: > infile < outfile cat will be relocated to : cat > infile < outfile
 * [REDIRECTION] [REDIRECTION] [COMMAND] ==> [COMMAND] [REDIRECTION] [REDIRECTION]
**/
int relocate(linked_list	*nodes_list);

/** This is the third pass, it injects basic redirection into command nodes. **/
/** Pipes are ignored for now. **/
int inject_redirection_into_nodes(linked_list	*nodes_list);

/** This is the four pass, it reorganizes the pipes. **/
/** Pipes are added into a stack, and then reorganized in the reverse order. And then, we pipe them and insert a redirection to each command nodes. **/
int	reorganize_pipes(linked_list	*nodes_list);

/** This is the fifth pass, it stuffs arguments into the command nodes. **/
int	analyze_command_argv(linked_list	*nodes_list);

/** This is the sixth pass, it builds a tree from tokens (on success, on fail, parallel execution)
 * Tokens are organized as: 
 *		- Simple & flag the previous command as "Run in background" mode.
 *		- AND is the left part of a binary tree
 *		- OR is the right part of a binary tree
 *		- Semicolon create a new AST
**/
t_ast	**build_tree(linked_list	*nodes_list);

#endif

#ifndef EXECUTE_AST_H_DEFINED
#define EXECUTE_AST_H_DEFINED

#include "parsing/ast.h"

#define SUCCESS 0
#define PARSING_ERROR 255
#define FORK_FAIL 254
#define SIGNAL_FAIL 253

int	execute_line(char	*line);
int execute_list_ast(t_ast_list	*list_ast);
int execute_ast(t_ast	*ast);
int execute_command(t_node_command	*cmd);

#endif

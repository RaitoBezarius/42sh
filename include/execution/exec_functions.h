#ifndef EXEC_FUNCTIONS_DEFINED
#define EXEC_FUNCTIONS_DEFINED

#include "parsing/ast.h"

int	standard_execute(t_node_command	*node);
int	execute_alias(t_node_command	*node);

#endif

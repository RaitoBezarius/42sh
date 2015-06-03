#ifndef CHILD_DEFINED_H
#define CHILD_DEFINED_H

#include "parsing/ast.h"

void	child_execute(t_node_command	*node);
int	install_signals_handlers();
int	install_redirection(t_node_command	*node);
int redirect(int from_fd, int to_fd);

#endif

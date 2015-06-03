#ifndef SIMPLE_REDIRECTION_H
#define SIMPLE_REDIRECTION_H

#include "utils/linked_list.h"
#include "parsing/state.h"

int	match_redirect_stdout(t_parse_state	*state);
int	match_redirect_stdin(t_parse_state	*state);

void	dispatch_redirection_stdout(t_parse_state	*state, t_linked_list	**current);
void	dispatch_redirection_stdin(t_parse_state	*state, t_linked_list	**current);

#endif

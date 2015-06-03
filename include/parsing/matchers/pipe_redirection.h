#ifndef PIPE_REDIRECTION_H
#define PIPE_REDIRECTION_H

#include "utils/linked_list.h"
#include "parsing/state.h"

int match_redirect_pipe(t_parse_state	*state);

void	dispatch_pipe_redirection(t_parse_state	*state, t_linked_list	**current);

#endif

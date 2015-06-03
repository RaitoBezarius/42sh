#ifndef EXECUTION_CHAIN_DEFINED
#define EXECUTION_CHAIN_DEFINED

#include "utils/linked_list.h"
#include "parsing/state.h"

int	match_token_and(t_parse_state	*state);
void	dispatch_token_and(t_parse_state	*state, t_linked_list	**current);

int match_token_or(t_parse_state	*state);
void	dispatch_token_or(t_parse_state	*state, t_linked_list	**current);

#endif

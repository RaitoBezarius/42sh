#ifndef EXECUTION_PARALLEL_DEFINED
#define EXECUTION_PARALLEL_DEFINED

#include "utils/linked_list.h"
#include "parsing/state.h"

int match_token_smcln(t_parse_state	*state);
void	dispatch_token_smcln(t_parse_state	*state, t_linked_list	**current);

int match_token_esperluette(t_parse_state	*state);
void	dispatch_token_esperluette(t_parse_state	*state, t_linked_list	**current);

#endif

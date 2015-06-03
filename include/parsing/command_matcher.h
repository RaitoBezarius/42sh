#ifndef COMMAND_MATCHER_H_DEFINED
#define COMMAND_MATCHER_H_DEFINED

#include "parsing/state.h"
#include "utils/linked_list.h"

void	command_freer(void	*item);
void	match_command(t_parse_state	*state, t_linked_list	**current);

#endif

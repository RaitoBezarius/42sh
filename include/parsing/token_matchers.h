#ifndef TOKEN_MATCHERS_DEFINED
#define TOKEN_MATCHERS_DEFINED

#include "parsing/state.h"
#include "parsing/ast.h"

int is_token(t_parse_state	*state);
void	match_token(t_parse_state	*state, t_ast	**current);

#endif

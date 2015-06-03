#ifndef TOKEN_MATCHERS_DEFINED
#define TOKEN_MATCHERS_DEFINED

#include "parsing/state.h"
#include "utils/linked_list.h"

typedef int (*token_matcher_function)(t_parse_state	*);
typedef void (*token_dispatcher_function)(t_parse_state	*, t_linked_list	**);

typedef struct s_token_definition
{
	int type;
	char const* name;
	token_matcher_function match;
	token_dispatcher_function dispatch;
} t_token_definition;

void	token_freer(void	*item);
int	get_token_type(t_parse_state	*state);
int is_token(t_parse_state	*state);
token_dispatcher_function	get_token_dispatcher(int type);
void	match_token(t_parse_state	*state, t_linked_list	**current);

enum TokenTypes
{
	TK_AND = 1,
	TK_OR = 2,
	TK_SMCLN = 3,
	TK_ESPERLUETTE = 4
};

extern t_token_definition token_defs[];

#endif

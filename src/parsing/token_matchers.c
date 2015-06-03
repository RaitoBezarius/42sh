#include "parsing/token_matchers.h"

#include "parsing/matchers/execution_chains.h"
#include "parsing/matchers/execution_parallel.h"

#include <stdlib.h>

t_token_definition token_defs[] = {
	{ TK_AND, "And (&&)", match_token_and, dispatch_token_and },
	{ TK_OR, "Or (||)", match_token_or, dispatch_token_or },
	{ TK_SMCLN, "Semicolon (;)", match_token_smcln, dispatch_token_smcln },
	{ TK_ESPERLUETTE, "Esperluette (&)", match_token_esperluette, dispatch_token_esperluette }
};

#define MAX_TOKEN_DEFS (int)(sizeof(token_defs) / sizeof(token_defs[0]))

void	token_freer(void	*item)
{
	int	*tk_type;

	tk_type = (int	*)item;
	free(tk_type);
}

int get_token_type(t_parse_state	*state)
{
	int index;
	int type;

	index = 0;
	type = 0;

	while (index < MAX_TOKEN_DEFS)
	{
		type = token_defs[index].match(state);
		if (type)
			return type;
		index++;
	}

	return type;
}

int is_token(t_parse_state	*state)
{
	return get_token_type(state) != 0;
}

token_dispatcher_function get_token_dispatcher(int type)
{
	int index;

	index = 0;
	while (index < MAX_TOKEN_DEFS)
	{
		if (token_defs[index].type == type)
			return token_defs[index].dispatch;
		index++;
	}

	return NULL;
}

void	match_token(t_parse_state	*state, t_linked_list	**current)
{
	int s_type = get_token_type(state);
	get_token_dispatcher(s_type)(state, current);
	(*current) = (*current)->next;
}

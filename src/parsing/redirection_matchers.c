#include "parsing/redirection_matchers.h"

static t_redirection_definition redir_defs[] = {
	{ REDIR_STDOUT, "Redirection to stdout", match_redirect_stdout, dispatch_redirection_stdout },

	{ REDIR_STDIN, "Redirection to stdin", match_redirect_stdin, dispatch_redirection_stdin },

	{ REDIR_PIPE, "Redirection by pipe", match_redirect_pipe, dispatch_pipe_redirection },
};

#define MAX_REDIR_DEFS (sizeof(redir_defs) / sizeof(redir_defs[0]))


int get_redir_type(t_parse_state	*state)
{
	int index;
	int type;

	index = 0;
	type = 0;

	while (index < MAX_REDIR_DEFS)
	{
		type = redir_defs[index].match(state);
		if (type)
			return type;
		index++;
	}

	return type;
}

int is_redirection(t_parse_state	*state)
{
	return get_redir_type(state) != 0;
}

redir_dispatcher_function	get_dispatcher(int type)
{
	int index;
	
	index = 0;

	while (index < MAX_REDIR_DEFS)
	{
		if (redir_defs[index].type == type)
			return redir_defs[index].dispatch;
	}

	return NULL;
}

void	match_redirection(t_parse_state	*state, t_linked_list	**current)
{
	int r_type = get_redir_type(state);
	get_dispatcher(r_type)(state, current);
}

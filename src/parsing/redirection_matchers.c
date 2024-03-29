#include "parsing/redirection_matchers.h"

#include "parsing/matchers/simple_redirection.h"
#include "parsing/matchers/pipe_redirection.h"

#include <stdlib.h>

static t_redirection_definition redir_defs[] = {
	{ REDIR_STDOUT, "Redirection to stdout", match_redirect_stdout, dispatch_redirection_stdout },

	{ REDIR_STDIN, "Redirection to stdin", match_redirect_stdin, dispatch_redirection_stdin },

	{ REDIR_PIPE, "Redirection by pipe", match_redirect_pipe, dispatch_pipe_redirection },
};

#define MAX_REDIR_DEFS (int)(sizeof(redir_defs) / sizeof(redir_defs[0]))

void	redirection_freer(void	*item)
{
	t_redirection	*redir;

	redir = (t_redirection	*)item;
	if (redir->filename)
	{
		free(redir->filename);
		redir->filename = NULL;
	}

	free(redir);
}

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

redir_dispatcher_function	get_redirection_matcher(int type)
{
	int index;
	
	index = 0;

	while (index < MAX_REDIR_DEFS)
	{
		if (redir_defs[index].type == type)
			return redir_defs[index].dispatch;
		index++;
	}

	return NULL;
}

void	match_redirection(t_parse_state	*state, t_linked_list	**current)
{
	int r_type = get_redir_type(state);
	get_redirection_matcher(r_type)(state, current);
}

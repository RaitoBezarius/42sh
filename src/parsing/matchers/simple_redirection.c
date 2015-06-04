#include "parsing/matchers/simple_redirection.h"
#include "parsing/redirection_matchers.h"
#include "parsing/ast.h"
#include "parsing/parse.h"
#include "parsing/error.h"

#include "utils/strcut.h"

#include "definitions.h"

#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	match_redirect_stdout(t_parse_state	*state)
{
	if (state->line[state->current_index] == '>' && state->line[state->current_index + 1] != '>')
		return REDIR_STDOUT;
	return FALSE;
}

int match_redirect_stdin(t_parse_state	*state)
{
	if (state->line[state->current_index] == '<' && state->line[state->current_index + 1] != '<')
		return REDIR_STDIN;
	return FALSE;
}

void	dispatch_redirection_stdout(t_parse_state	*state, t_linked_list	**current)
{
	t_redirection	*redirection;

	state->current_index++;
	skipPast(state, ' ');
	state->start_index = state->current_index;
	skipToNext(state, ' ');
	redirection = create_redirection();
	redirection->type = REDIR_STDOUT;
	redirection->filename = strcut(state->line, state->start_index, state->current_index - 1);
	if (!open_fd(state, redirection, O_WRONLY))
		return;
	push_to_linked_list((*current), redirection, ITEM_REDIRECTION, redirection_freer);
	(*current) = (*current)->next;
	state->current_index++;
}

void	dispatch_redirection_stdin(t_parse_state	*state, t_linked_list	**current)
{
  t_redirection	*redirection;

	state->current_index++;
	skipPast(state, ' ');
	state->start_index = state->current_index;
	skipToNext(state, ' ');
	if (state->start_index == state->current_index)
	{
		set_error(state, "File has not been provided for redirection!\n");
		return;
	}
	redirection = create_redirection();
	redirection->type = REDIR_STDIN;
	redirection->filename = strcut(state->line, state->start_index, state->current_index - 1);
	if (!open_fd(state, redirection, O_RDONLY))
		return;
	push_to_linked_list((*current), redirection, ITEM_REDIRECTION, redirection_freer);
	(*current) = (*current)->next;
	state->current_index++;
}

int	open_fd(t_parse_state	*state, t_redirection	*redirection, int flag)
{
	redirection->fd = open(redirection->filename, flag);
	if (redirection->fd < 0)
	{
		set_error(state, "%s: %s\n", strerror(errno), redirection->filename);
		return FALSE;
	}
	return TRUE;
}

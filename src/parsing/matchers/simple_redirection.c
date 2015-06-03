#include "parsing/matchers/simple_redirection.h"

#include "definitions.h"

int	match_redirect_stdout(t_parse_state	*state)
{
	if (state->line[state->current_index] == '>' && state->line[state->current_index + 1] != '>')
		return TRUE;
	return FALSE;
}

int match_redirect_stdin(t_parse_state	*state)
{
	if (state->line[state->current_index] == '<' && state->line[state->current_index + 1] != '<')
		return TRUE;
	return FALSE;
}

void	dispatch_redirection_stdout(t_parse_state	*state, t_linked_list	**current)
{
	char	*filename;
	t_redirection	*redirection;

	state->current_index++;
	while (state->line[state->current_index] == ' ')
		state->current_index++;
	
	state->start_index = state->current_index;

	while (state->line[state->current_index] != ' ')
		state->current_index++;

	redirection = create_redirection();
	redirection->type = REDIR_STDOUT;
	redirection->filename = strcut(state->line, state->start_index, state->current_index - 1);
	redirection->fd = open(redirection->filename, O_WDONLY);
	if (redirection->fd < 0)
	{
		set_error(state, "No such file or directory: %s", redirection->filename);
		return;
	}
	push_to_linked_list((*current), redirection, ITEM_COMMAND);
	(*current) = (*current)->next;
}

void	dispatch_redirection_stdin(t_parse_state	*state, t_linked_list	**current)
{
	char	*filename;
  t_redirection	*redirection;

	state->current_index++;
	while (state->line[state->current_index] == ' ')
		state->current_index++;
	
	state->start_index = state->current_index;

	while (state->line[state->current_index] != ' ')
		state->current_index++;

	redirection = create_redirection();
	redirection->type = REDIR_STDIN;
	redirection->filename = strcut(state->line, state->start_index, state->current_index - 1);
	redirection->fd = open(redirection->filename, O_RDONLY);
	if (redirection->fd < 0)
	{
		set_error(state, "No such file or directory: %s", redirection->filename);
		return;
	}
	push_to_linked_list((*current), redirection, ITEM_COMMAND);
	(*current) = (*current)->next;
}

#include "parsing/parse.h"
#include "parsing/ast.h"
#include "parsing/state.h"
#include "parsing/error.h"

#include "parsing/redirection_matchers.h"
#include "parsing/token_matchers.h"
#include "parsing/command_matcher.h"
#include "parsing/parse_passes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_ast_list	*parse_line(char	*line)
{
	t_linked_list	*nodes_list;
	t_ast_list	*list_ast;
	int	index;

	nodes_list = form_initial_list(line);
	index = 0;

	if (nodes_list == NULL)
		return NULL;

	while (index < N_PASSES)
	{
		if (!passes[index](&nodes_list))
			return NULL;
		index++;
	}

	print_debug_list(nodes_list);

	list_ast = build_tree(nodes_list);
	if (!list_ast)
	{
		free_linked_list(nodes_list);
		return NULL;
	}
	
	free_linked_list(nodes_list);
	return list_ast;
}

t_linked_list	*form_initial_list(char	*line)
{
	t_parse_state	*state;
	t_linked_list	*start;
	t_linked_list	*current;
	
	state = init_parse_state(line);
	start = create_linked_list();
	if (!state || !start)
		return NULL;
	current = start;
	while (state->current_index < state->line_length)
	{
		if (is_redirection(state))
			match_redirection(state, &current);
		else if (is_token(state))
			match_token(state, &current);
		else
			match_command(state, &current);
		if (!state->bit_ok)
		{
			panic(state);
			return NULL;
		}
		skipPast(state, ' ');
	}
	if (!current->item || !current->type)
		remove_linked_item(current);

	free(state);
	return start;
}

t_ast_list	*build_tree(t_linked_list	*nodes_list)
{
	t_ast_list	*tree;

	return NULL;
}

void	skipPast(t_parse_state	*state, char character)
{
	while (state->line[state->current_index] == character && state->current_index < state->line_length)
		state->current_index++;
}

void skipToNext(t_parse_state	*state, char character)
{
	while (state->line[state->current_index] != character && state->current_index < state->line_length)
		state->current_index++;
}

static char	*get_string_array(char	**argv)
{
	char	*str;
	int arg_len;
	int available_size;
	int total_size;
	int cur_pos;
	int index;

	total_size = 32;
	available_size = 32;
	cur_pos = 0;
	index = 0;

	str = calloc(32, sizeof(char));

	str[0] = '[';

	cur_pos += 1;
	available_size -= 1;

	if (argv != NULL)
	{
		while (argv[index] != NULL)
		{
			if (index == 0)
			{
				strcat(&str[cur_pos], " ");
				available_size--;
				cur_pos++;
			}
			else
			{
				strcat(&str[cur_pos], ", ");
				available_size -= 2;
				cur_pos += 2;
			}

			arg_len = strlen(argv[index]);
			if (available_size <= arg_len)
			{
				total_size += (arg_len - available_size + 1);
				str = realloc(str, total_size);
				available_size += (arg_len + 1);
			}
			strcat(&str[cur_pos], argv[index]);
			available_size -= arg_len;
			cur_pos += arg_len;
			index++;
		}
	}

	if (available_size < 3)
	{
		total_size += (3 - available_size);
		str = realloc(str, total_size);
	}
	
	str[cur_pos] = ' ';
	str[cur_pos + 1] = ']';
	str[cur_pos + 2] = '\0';

	return str;
}
void	print_debug_list(t_linked_list	*nodes_list)
{
	while (nodes_list)
	{
		printf(" ==> ");
		print_debug_node(nodes_list);
		nodes_list = nodes_list->next;
	}
	printf("\n");
}

void	print_debug_node(t_linked_list	*node)
{
	t_redirection	*tnode;
	t_node_command	*cnode;
	char	*str_argv;
	int index;

	if (node->type == ITEM_COMMAND)
	{
		cnode = (t_node_command	*)node->item;
		str_argv = get_string_array(cnode->argv);
		printf("Command, exe: %s, argv: %s, in: %p, out: %p", cnode->executable, str_argv, (int*)cnode->in, (int*)cnode->out);
		free(str_argv);
	}
	else if (node->type == ITEM_REDIRECTION)
	{
		tnode = (t_redirection	*)node->item;
		if (tnode->filename)
			printf("Redirection, type: %d, filename: %s, fd: %d", tnode->type, tnode->filename, tnode->fd);
		else
			printf("Redirection, type: %d, fd: %d", tnode->type, tnode->fd);
	}
	else
	{
		int tk = *((int *)node->item);
		index = 0;
		while (index < 4 && token_defs[index].type != tk)
			index++;
		printf("Token: %s", token_defs[index].name);
	}
}


/*
** parse.c for 42sh in /home/bebe-b_h/projects/42sh/src/parsing
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri Jun 05 08:23:17 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:33:21 2015 BEBE-BELL Hendy-Wilson
*/

#include "parsing/parse.h"
#include "parsing/ast.h"
#include "parsing/state.h"
#include "parsing/error.h"

#include "parsing/redirection_matchers.h"
#include "parsing/token_matchers.h"
#include "parsing/command_matcher.h"
#include "parsing/parse_passes.h"

#include "definitions.h"

#include "utils.h"

#include <unistd.h>
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

  /* print_debug_list(nodes_list); */

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
    remove_linked_item(current, TRUE);

  free(state);
  return start;
}


t_node_command	*copy_node(t_node_command	*original)
{
  t_node_command	*cmd;
  int len_exe;

  cmd = create_node();
  len_exe = strlen(original->executable);
  cmd->executable = malloc((len_exe + 1) * sizeof(char));
  strcpy(cmd->executable, original->executable);
  cmd->executable[len_exe] = '\0';
  cmd->argv = str_to_wordtab(cmd->executable, ' ');
  cmd->flag_background = original->flag_background;
  cmd->execute = original->execute;
  cmd->out = copy_redirection(original->out);
  cmd->in = copy_redirection(original->in);

  return cmd;
}

t_redirection	*copy_redirection(t_redirection	*original)
{
  t_redirection	*redir;
  int len_file;

  if (!original)
    return NULL;

  redir = create_redirection();
  redir->type = original->type;
  redir->way = original->way;

  if (original->filename)
  {
    len_file = strlen(original->filename);
    redir->filename = malloc(sizeof(char) * (len_file + 1));
    strcpy(redir->filename, original->filename);
    redir->filename[len_file] = '\0';
  }

  if (original->fd != 0)
    dup2(original->fd, redir->fd);

  return redir;
}

t_ast	*build_sub_tree(t_ast_list	*ast_list, int index, t_linked_list	**list)
{
  t_ast	*ast;
  t_node_command	*cmd;
  int	tk_type;

  if (!(*list))
    return NULL;

  ast = create_ast();
  if (!ast)
    return NULL;

  while ((*list))
  {
    if ((*list)->type == ITEM_COMMAND)
    {
      cmd = copy_node((*list)->item);
      ast->node = cmd;
    }
    else if ((*list)->type == ITEM_TOKEN)
    {
      tk_type = *((int*)(*list)->item);
      if (tk_type == TK_AND)
	ast->on_command_succeed = build_sub_tree(ast_list, index, &((*list)->next));
      else if (tk_type == TK_OR)
	ast->on_command_failed = build_sub_tree(ast_list, index, &((*list)->next));
      else if (tk_type == TK_SMCLN)
      {
	index++;
	ast_list->list = realloc(ast_list->list, sizeof(t_ast	*) * (index + 1));
	ast_list->list[index] = build_sub_tree(ast_list, index, &((*list)->next));
      }
      else if (tk_type == TK_ESPERLUETTE)
	ast->node->flag_background = TRUE;
    }

    if ((*list))
      (*list) = (*list)->next;
  }

  return ast;
}

t_ast_list	*build_tree(t_linked_list	*nodes_list)
{
  t_ast_list	*tree;

  tree = malloc(sizeof(t_ast_list));
  tree->list = calloc(1, sizeof(t_ast	*));
  tree->n_ast = 1;
  tree->list[0] = build_sub_tree(tree, 0, &nodes_list);

  return tree;
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
    printf("Command, exe: %s, argv: %s, in: %p, out: %p", cnode->executable,
	str_argv, (void *)cnode->in, (void *)cnode->out);
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


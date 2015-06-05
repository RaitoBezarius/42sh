#include "execution/execute_ast.h"
#include "execution/child.h"

#include "parsing/parse.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

static int	is_blank_line(char *line)
{
  int		i;

  i = 0;
  while (line[i])
  {
    if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
      return (0);
    ++i;
  }
  return (1);
}

int		execute_line(char *line)
{
  t_ast_list	*list_ast;

  if (is_blank_line(line))
    return (0);
  list_ast = parse_line(line);
  if (!list_ast)
    return (PARSING_ERROR);
  return (execute_list_ast(list_ast));
}

int	execute_list_ast(t_ast_list *list_ast)
{
  int	index;
  int	ret_code;

  index = 0;
  ret_code = SUCCESS;
  while (index < list_ast->n_ast)
  {
    ret_code = execute_ast(list_ast->list[index]);
    index++;
  }
  return (ret_code);
}

int			execute_ast(t_ast *ast)
{
  t_node_command	*cmd;
  int			status_code;

  cmd = ast->node;
  status_code = execute_command(cmd);
  if (status_code != 0)
  {
    if (!ast->on_command_failed)
      return (status_code);
    else
      execute_ast(ast->on_command_failed);
  }
  else
  {
    if (!ast->on_command_succeed)
      return (status_code);
    else
      execute_ast(ast->on_command_succeed);
  }
  return (SUCCESS);
}

int	execute_command(t_node_command *cmd)
{
  int	status;
  pid_t	childpid;

  if ((childpid = fork()) < 0)
  {
    fprintf(stderr, "Fork failed. Aborting execution.");
    return (FORK_FAIL);
  }

  if (childpid != 0)
  {
		/** TODO: Install SIGINT handler **/
    waitpid(childpid, &status, 0);
    return (status);
  }
  else
  {
    child_execute(cmd);
    return (0);
  }
}

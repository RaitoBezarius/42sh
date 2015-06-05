/*
** child.c for 42sh in /home/bebe-b_h/projects/42sh/src/execution
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri Jun 05 07:48:24 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 07:52:22 2015 BEBE-BELL Hendy-Wilson
*/

#include "execution/child.h"
#include "execution/execute_ast.h"
#include "execution/signal_handler.h"

#include "definitions.h"

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void	child_execute(t_node_command *cmd)
{
  int	error;

  if (!install_signals_handlers())
    return ;
  if (!install_redirection(cmd))
    return ;
  error = cmd->execute(cmd);
  if (error == -1)
    fprintf(stderr, "Execve failed. Aborting execution: %s.\n",
	    strerror(errno));
}

int	install_signals_handlers()
{
  if (signal(SIGSEGV, onSegmentationFault) == SIG_ERR)
  {
    fprintf(stderr, "Failed to install signal handler (SIGSEGV): %s\n",
	    strerror(errno));
    return (SIGNAL_FAIL);
  }
  if (signal(SIGILL, onIllegalInstruction) == SIG_ERR)
  {
    fprintf(stderr, "Failed to install signal handler (SIGILL): %s\n",
	    strerror(errno));
    return (SIGNAL_FAIL);
  }
  if (signal(SIGABRT, onAbnormalAbortion) == SIG_ERR)
  {
    fprintf(stderr, "Failed to install signal handler (SIGABRT): %s\n",
	    strerror(errno));
    return (SIGNAL_FAIL);
  }
  if (signal(SIGTERM, onTerminated) == SIG_ERR)
  {
    fprintf(stderr, "Failed to install signal handler (SIGTERM): %s\n",
	    strerror(errno));
    return (SIGNAL_FAIL);
  }
  return (TRUE);
}

int	install_redirection(t_node_command *cmd)
{
  if (cmd->in && !redirect(cmd->in->fd, STDIN_FILENO))
  {
    fprintf(stderr, "Failed to redirect stdin: %s\n", strerror(errno));
    return (FALSE);
  }
  if (cmd->out && !redirect(cmd->out->fd, STDOUT_FILENO))
  {
    fprintf(stderr, "Failed to redirect stdout: %s\n", strerror(errno));
    return (FALSE);
  }
  return (TRUE);
}

int	redirect(int from_fd, int to_fd)
{
  if (dup2(from_fd, to_fd) < 0)
  {
    fprintf(stderr, "Failed to duplicate file descriptor.");
    return (FALSE);
  }
  if (close(from_fd) < 0)
  {
    fprintf(stderr, "Failed to close file descriptor.");
    return (FALSE);
  }
  return (TRUE);


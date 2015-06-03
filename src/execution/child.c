#include "execution/child.h"

void	child_execute(t_node_command	*cmd)
{
	int error;

	if (!install_signals_handlers())
		return ;
	if (!install_redirection(cmd))
		return ;
	error = execve(cmd->executable, cmd->argv);
	if (error == -1)
		fprintf(stderr, "Execve failed. Aborting execution.");
}

int	install_signals_handlers()
{
	
}

int	install_redirection(t_node_command	*cmd)
{
	if (cmd->in && !redirect(cmd->in->fd, STDIN_FILENO))
	{
		fprintf(stderr, "Failed to redirect stdin.");
		return FALSE;
	}
	if (cmd->out && !redirect(cmd->out->fd, STDOUT_FILENO))
	{
		fprintf(stderr, "Failed to redirect stdout.");
		return FALSE;
	}
	return TRUE;
}

int redirect(int from_fd, int to_fd)
{
	if (dup2(from_fd, to_fd) < 0)
	{
		fprintf(stderr, "Failed to duplicate file descriptor.");
		return FALSE;
	}
	if (close(from_fd) < 0)
	{
		fprintf(stderr, "Failed to close file descriptor.");
		return FALSE;
	}
	return TRUE;
}

#include "execution/exec_functions.h"

#include <unistd.h>

int	standard_execute(t_node_command	*node)
{
	/** TODO: search_in_path(node->argv[0]) **/
	/** TODO: Check if argv is correctly passed and as for envp do it yourself. **/
	return execve(node->argv[0], node->argv, NULL);
}

int execute_alias(t_node_command	*node)
{
	/** TODO: Search alias and replace it by its correspondance. **/
	/** When it is done, check if it is a builtin, if it is, dispatch the call to the builtin. **/
	/** If not, call standard_execute with the node modified. **/
	return 0;
}

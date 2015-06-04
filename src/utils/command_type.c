#include "utils/command_type.h"
#include "alias.h"
#include "builtins.h"

#include "definitions.h"

#include <string.h>

int	is_alias(char	*executable)
{
	t_alias	*current;

	current = g_alias_list;
	while (current)
	{
		if (strcmp(current->name, executable) == 0)
			return TRUE;
		current = current->next;
	}
	return FALSE;
}

int is_builtin(char	*executable)
{
	int index;
	
	index = 0;
	while (g_builtins[index].name != NULL)
	{
		if (strcmp(g_builtins[index].name, executable) == 0)
			return TRUE;
		index++;
	}
	return FALSE;
}

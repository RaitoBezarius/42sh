#include "parsing/parse_utils.h"

#include "definitions.h"

int	expect(t_linked_list	**current, int type)
{
	if (!(*current))
		return FALSE;

	if ((*current)->type != type)
		return FALSE;
	else
	{
		(*current) = (*current)->next;
		return TRUE;
	}
}

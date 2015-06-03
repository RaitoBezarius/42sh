#include "utils/linked_list.h"

#include <stdlib.h>

t_linked_list	*create_linked_list()
{
	t_linked_list	*list;

	list = malloc(sizeof(t_linked_list));
	if (!list)
	{
		fprintf(stderr, "Allocation failed!");
		return NULL;
	}
	list->next = NULL;
	list->prev = NULL;
	list->item = NULL;
	list->type = 0;
	return list;
}

void	free_linked_list(t_linked_list	*list)
{
	free(list->item);
	while (list = list->next)
	{
		free(list->item);
		free(list->prev);
	}
}

void	remove_linked_item(t_linked_list	*item)
{
	free(item->item);
	if (item->next)
		item->prev->next = item->next;
	if (item->prev)
		item->next->prev = item->prev;
	free(item);
}

void	move_item_before(t_linked_list	*from, t_linked_list	*to)
{
	if (from->prev)
		from->prev->next = from->next;
	if (from->next)
		from->next->prev = from->prev;

	if (to->prev)
	{
		from->prev = to->prev;
		from->prev->next = from;
	}

	to->prev = from;
}

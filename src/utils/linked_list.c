#include "utils/linked_list.h"

#include <stdio.h>
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
	t_linked_list	*next;

	while (list)
	{
		next = list->next;

		list->freer(list->item);
		free(list);

		list = next;
	}
}

void	push_to_linked_list(t_linked_list	*current, void	*item, int	type, free_f_ptr	freer)
{
	current->item = item;
	current->type = type;
	current->freer = freer;
	current->next = create_linked_list();
	current->next->prev = current;
}

void	remove_linked_item(t_linked_list	*item)
{
	free(item->item);

	if (item->next && item->prev)
	{
		item->prev->next = item->next;
		item->next->prev = item->prev;
	}
	else if (item->next)
		item->next->prev = NULL;
	else if (item->prev)
		item->prev->next = NULL;

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

#ifndef LINKED_LIST_H_DEFINED
#define LINKED_LIST_H_DEFINED

typedef struct s_linked_list
{
	struct s_linked_list	*next;
	struct s_linked_list	*prev;
	void	*item;
	int	type;
} t_linked_list;

/** Basic allocation function **/
t_linked_list	*create_linked_list();
void	free_linked_list(t_linked_list	*list);

/** Linked list manipulation functions **/
void	push_to_linked_list(t_linked_list	*current, void	*item, int	type);
void	remove_linked_item(t_linked_list	*item);
void	move_item_before(t_linked_list	*from, t_linked_list	*to);

#endif

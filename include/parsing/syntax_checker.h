#ifndef SYNTAX_CHECKER_DEFINED
#define SYNTAX_CHECKER_DEFINED

#define FAILED 0
#define CONTINUE 1
#define FINISHED 2

#include "utils/linked_list.h"

void	no_freer(void	*ptr);
t_linked_list	*transform_syntax(t_linked_list	*nodes);
int	check_syntax(t_linked_list	**nodes_list);
int	expect_block(t_linked_list	**nodes_list);
int	expect_token(t_linked_list	**nodes_list);

#endif

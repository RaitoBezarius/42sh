#ifndef REDIRECTION_MATCHERS_DEFINED
#define REDIRECTION_MATCHERS_DEFINED

#include "parsing/ast.h"
#include "parsing/state.h"
#include "utils/linked_list.h"

typedef int (*redir_matcher_function)(t_parse_state	*);
typedef void (*redir_dispatcher_function)(t_parse_state	*, t_linked_list	**);

typedef struct s_redirection_definition
{
	int type;
	char const* name;
	redir_matcher_function match;
	redir_dispatcher_function dispatch;
} t_redirection_definition;

void	redirection_freer(void	*redirection);
int get_redir_type(t_parse_state	*state);
int is_redirection(t_parse_state	*state);
redir_dispatcher_function	get_redirection_dispatcher(int type);
void	match_redirection(t_parse_state	*state, t_linked_list	**current);

enum RedirectionTypes
{
	REDIR_STDOUT = 1,
	REDIR_STDIN = 2,
	REDIR_PIPE = 3,
	REDIR_STDIN_EOL = 4,
	REDIR_STDOUT_APP = 5
};

enum RedirectionWay
{
	INPUT = 1,
	OUTPUT = 2
};

#endif

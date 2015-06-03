#ifndef AST_H_DEFINED
#define AST_H_DEFINED

typedef struct s_redirection
{
	int type;
	int way;
	char	*filename;
	int	fd;
} t_redirection;

typedef struct s_node_command
{
	char	*executable;
	char	**argv;
	t_redirection	*out;
	t_redirection	*in;
	int flag_background;
} t_node_command;

typedef struct s_ast
{
	struct s_ast	*on_command_succeed;
	struct s_ast	*on_command_failed;
	
	t_node_command	*node;
} t_ast;

typedef struct s_ast_list
{
	t_ast	**list;
	int n_ast;
} t_ast_list;

/** Basic allocation functions **/
t_ast	*create_ast();
t_node_command	*create_node();
t_redirection	*create_redirection();


enum ListItem
{
	ITEM_COMMAND = 1,
	ITEM_REDIRECTION = 2,
	ITEM_TOKEN = 3
};

#endif

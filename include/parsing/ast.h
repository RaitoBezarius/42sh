/*
** ast.h for 42sh in /home/bebe-b_h/projects/42sh/include/parsing
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri Jun 05 08:07:39 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:08:36 2015 BEBE-BELL Hendy-Wilson
*/

#ifndef AST_H_
#define AST_H_

typedef struct	s_redirection
{
  int		type;
  int		way;
  char		*filename;
  int		fd;
}		t_redirection;

typedef struct	s_node_command
{
  char		*executable;
  char		**argv;
  t_redirection	*out;
  t_redirection	*in;
  int		flag_background;
  int		(*execute)(struct s_node_command *);
}		t_node_command;

typedef struct		s_ast
{
  struct s_asti		*on_command_succeed;
  struct s_ast		*on_command_failed;
  t_node_command	*node;
}			t_ast;

typedef struct s_ast_list
{
  t_ast		**list;
  int		n_ast;
}		t_ast_list;

/*
** Basic allocation functions
*/
t_ast		*create_ast();
t_node_command	*create_node();
t_redirection	*create_redirection();
int		*create_token(int tk_type);

/*
** 4 is Special use for the syntax checker
*/
enum ListItem
{
  ITEM_COMMAND = 1,
  ITEM_REDIRECTION = 2,
  ITEM_TOKEN = 3,
  ITEM_PIPE = 4
};

#endif /* !AST_H_ */

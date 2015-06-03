/*
** utils.h for 42sh in /home/bebe-b_h/rendu/42sh
** 
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.net>
** 
** Started on  Mon May 11 19:14:38 2015 BEBE-BELL Hendy-Wilson
** Last update Fri May 15 17:46:01 2015 Alban Meurice
*/

#ifndef UTILS_H_
# define UTILS_H_

# include <stdio.h>

typedef struct	s_tree
{
  int		type;
  char		*cmd;
  char		**args;
}		t_tree;

/*
** Types
*/
# define	REDIR_L
# define	REDIR_R
# define	DREDIR_L
# define	DREDIR_R
# define	PIPE
# define	DPIPE

/*
** Macros
*/

# define ERROR(x)	(fprintf(stderr, "Error: %s\n", (x)))
# define MAX_HISTORY	(10)

/*
** System Errors
*/
# define ERR_ALLOC	"couldn't allocate memory"

/*
** Program Errors
*/
# define ERR_CMDNF	"command not found"

/*
** Program functions
*/

int		show_prompt(void);
int		history_func(char *);
char		**add_line_history(char **, char *);
int		update_history();
int		new_history(int);
int		func_close_open(int);
int		new_line_history(char *);

/*
** env functions
*/

char		**copy_env(char **);

/*
** Output functions
*/
char		*str_error(char *str, char *function);

/*
**  Utility functions
*/
size_t		my_strlen(const char *);
size_t		strclen(const char *, const char);
size_t		count_words(const char *, const char);
char		**str_to_wordtab(const char *, const char);
int		check_before_end(char *str, char charactere);
char		*find_path(char **env);
char		**split_path(char *path);
char		*find_binary(char *binary, char **path);
char		**create_new_tab(char **, char *);
void		show_tab(char **);
char		*my_strdup(const char *);
int		my_putstr(const char *);
int		my_putchar(const char);

#endif /* !UTILS_H_ */

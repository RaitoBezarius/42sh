/*
** env.h for 42sh in /home/bebe-b_h/rendu/42sh/src/env
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 03:40:00 2015 BEBE-BELL Hendy-Wilson
** Last update Sun May 24 16:25:22 2015 BEBE-BELL Hendy-Wilson
*/

#ifndef ENV_H_
# define ENV_H_

typedef struct	s_env
{
  char		*name;
  char		*value;
  struct s_env	*next;
}		t_env;

void		load_env(char **envp); /** <== TODO: this function **/
int		my_setenv(const char *name, const char *value);
int		my_unsetenv(const char **name_list);
int		my_printenv(const char *name);

extern t_env	*g_env_list;

#endif /* !ENV_H_ */

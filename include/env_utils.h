/*
** env_utils.h for 42sh in /home/bebe-b_h/rendu/42sh/src/env
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Sun May 24 12:25:27 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:49:57 2015 BEBE-BELL Hendy-Wilson
*/

#ifndef ENV_UTILS_H_
# define ENV_UTILS_H_

t_env	*get_env(const char *nane);
t_env	*create_env_var(const char *name);
void	init_envvars(char **envp);

#endif /* !ENV_UTILS_H_ */

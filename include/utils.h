/*
** utils.h for 42sh in /home/bebe-b_h/rendu/42sh
** 
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.net>
** 
** Started on  Mon May 11 19:14:38 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:30:59 2015 BEBE-BELL Hendy-Wilson
*/

#ifndef UTILS_H_
# define UTILS_H_

#include <unistd.h>

/*
** System Errors
*/
# define ERR_ALLOC	"could not allocate memory"

/*
** Program Errors
*/
# define ERR_CMDNF	"command not found"

/*
** Program functions
*/
int		show_prompt(void);

/*
**  Utility functions
*/
size_t		my_strlen(const char *);
size_t		strclen(const char *, const char);

size_t		count_words(const char *, const char);
char		**str_to_wordtab(const char *, const char);
void		free_wordtab(char **wordtab);

#endif /* !UTILS_H_ */

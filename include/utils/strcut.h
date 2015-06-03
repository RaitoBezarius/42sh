/*
** strcut.h for header in /home/bebe-b_h/projects/42sh
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri May 22 16:34:39 2015 BEBE-BELL Hendy-Wilson
** Last update Fri May 22 16:34:55 2015 BEBE-BELL Hendy-Wilson
*/

#ifndef STRCUT_H_
# define STRCUT_H_

typedef struct s_strip_location
{
	int start_index;
	int end_index;
} t_strip_location;

/** TODO: Stripper les tabulations aussi, je le sens pas... **/
int is_blank(char c);
t_strip_location count_stripped(const char *line, const int start, const int end);
char	*strcut(const char *line, const int start, const int end);

#endif /* !STRCUT_H_ */

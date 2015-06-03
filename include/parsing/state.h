#ifndef STATE_H_DEFINED
#define STATE_H_DEFINED

typedef struct s_parse_state
{
	const char	*line;
	int line_length;
	int current_index;
	int start_index;
} t_parse_state;

/** Basic allocation function **/
s_parse_state	*initialize_parse_state(char	*line);

#endif

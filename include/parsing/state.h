#ifndef STATE_H_DEFINED
#define STATE_H_DEFINED

typedef struct s_parse_state
{
	const char	*line;
	int line_length;
	int current_index;
	int start_index;
	int bit_ok;
} t_parse_state;

/** Basic allocation function **/
t_parse_state	*init_parse_state(char	*line);

#endif

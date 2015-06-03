#ifndef ERROR_DEFINED_H
#define ERROR_DEFINED_H

#include <stdarg.h>
#include "parsing/state.h"

void	set_error(t_parse_state	*state, const char	*format, ...);
void	panic(t_parse_state	*state);

#endif

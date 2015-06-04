#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/get_next_line.h"
#include "execution/execute_ast.h"


int main(int argc, char	**argv)
{
	char	*line;
	int	status_code;
	
	while (1)
	{
		printf("> ");
		fflush(stdout);
		line = get_next_line(0);

		if (strcmp(line, "exit") == 0 || !line)
		{
			free(line);
			return 0;
		}

		if (strcmp(line, "") == 0)
		{
			free(line);
			continue;
		}
		
		status_code = execute_line(line);
		free(line);
		if (status_code != 0)
			printf("Returned %d.\n", status_code);
	}

	return 0;
}

#ifndef PARSE_PASSES_H_DEFINED
#define PARSE_PASSES_H_DEFINED

#include "utils/linked_list.h"

/** This is the first pass, it will check the syntax and relocate pre-fix / post-fix elements.
 * Example: > infile < outfile cat will be relocated to : cat > infile < outfile
 * [REDIRECTION] [REDIRECTION] [COMMAND] ==> [COMMAND] [REDIRECTION] [REDIRECTION]
**/
int relocate(t_linked_list	*nodes_list);

/** This is the second pass, it injects basic redirection into command nodes. **/
/** Pipes are ignored for now. **/
int inject_redirection_into_nodes(t_linked_list	*nodes_list);

/** This is the third pass, it reorganizes the pipes. **/
/** Pipes are added into a stack, and then reorganized in the reverse order. And then, we pipe them and insert a redirection to each command nodes. **/
int	reorganize_pipes(t_linked_list	*nodes_list);

/** This is the fourth pass, it stuffs arguments into the command nodes. **/
int	analyze_command_argv(t_linked_list	*nodes_list);

typedef int (*pass_function)(t_linked_list	*);
extern pass_function passes[3];
#define N_PASSES 3
#endif

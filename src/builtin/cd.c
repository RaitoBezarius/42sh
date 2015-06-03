/*
** cd.c for 42sh in /home/bebe-b_h/projects/42sh/src/builtin
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Wed Jun 03 21:58:17 2015 BEBE-BELL Hendy-Wilson
** Last update Wed Jun 03 22:07:33 2015 BEBE-BELL Hendy-Wilson
*/

#include <stdlib.h>

#include "env_utils.h"

int	cd(char **args)
{
  if (args == NULL || args[0] == NULL)
    /* CHDIR VERS LE HOME */
    ;
  else if (STREQ(args[0], "-"))
    /* BACK TO OLD PATH */
    ;

}

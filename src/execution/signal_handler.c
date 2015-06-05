/*
** signal_handler.c for 42sh in /home/bebe-b_h/projects/42sh/src/execution
**
** Made by BEBE-BELL Hendy-Wilson
** Login   <bebe-b_h@epitech.eu>
**
** Started on  Fri Jun 05 07:56:30 2015 BEBE-BELL Hendy-Wilson
** Last update Fri Jun 05 08:28:33 2015 BEBE-BELL Hendy-Wilson
*/

#include "execution/signal_handler.h"

#include <stdio.h>

void	onSegmentationFault(int parameter)
{
  (void) parameter;
  fprintf(stderr, "Segmentation fault.\n");
}

void	onIllegalInstruction(int parameter)
{
  (void) parameter;
  fprintf(stderr, "Illegal instruction.\n");
}

void	onAbnormalAbortion(int parameter)
{
  (void) parameter;
  fprintf(stderr, "Abnormal abortion.\n");
}

void	onTerminated(int parameter)
{
  (void) parameter;
  fprintf(stderr, "Program terminated.\n");
}

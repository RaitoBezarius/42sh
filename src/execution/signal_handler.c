#include "execution/signal_handler.h"

#include <stdio.h>

void	onSegmentationFault(int parameter)
{
	fprintf(stderr, "Segmentation fault.\n");
}

void onIllegalInstruction(int	parameter)
{
	fprintf(stderr, "Illegal instruction.\n");
}

void onAbnormalAbortion(int parameter)
{
	fprintf(stderr, "Abnormal abortion.\n");
}

void onTerminated(int parameter)
{
	fprintf(stderr, "Program terminated.\n");
}

#ifndef SIGNAL_HANDLER_DEFINED
#define SIGNAL_HANDLER_DEFINED

void	onSegmentationFault(int	parameter);
void	onIllegalInstruction(int	parameter);
void	onAbnormalAbortion(int	parameter);
void	onTerminated(int	parameter);

#endif

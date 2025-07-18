#include "../../include/executor.h"

int	count_char_array(char **commands)
{
	int	i;

	if (!commands)
		return (0);
	i = 0;
	while (commands[i])
		i++;
	return (i);
}
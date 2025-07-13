#include "../../include/executor.h"

void	check_init(size_t *i, int *j, int *k, int *digit)
{
	*i = 0;
	*j = 0;
	*k = 1;
	*digit = 0;
}

int	str_index(const char *str, int ch)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == ch)
			return (index);
		index++;
	}
	return (-1);
}

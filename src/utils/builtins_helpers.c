#include "../../include/executor.h"

int	ft_strslen(char **strs)
{
	int i = 0;
	if (!strs)
		return (0);
	while (strs[i])
		i++;
	return (i);
}

int	overflow_check(size_t test, int digit)
{
	if (test > LLONG_MAX / 10 || (test == LLONG_MAX / 10
			&& (digit > LLONG_MAX % 10)))
		return (2);
	return (0);
}

int	undeflow_check(size_t min_limit, size_t test, int digit, int last)
{
	if (test > min_limit || (test == min_limit && digit > last))
		return (2);
	return (0);
}

void	edit_env(t_env *head, char *key, char *new_value)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp(current->name, key))
		{
			current->value = new_value;
			return ;
		}
		current = current->next;
	}
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dup;

	if (!s)
		return (NULL);
	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void free_data(t_data *data)
{	
    garbage_removal(&(data->alloc)); // if this is generic
    free(data);
    data = NULL;
    rl_clear_history();
}

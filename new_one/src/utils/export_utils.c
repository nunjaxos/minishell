#include "../../include/executor.h"

int	check_valid_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	export_not_valid(char *tmp, int *i, char *value, char *key, t_data *data)
{
	tmp = ft_strjoin_malloc("=", value, data);  // safe allocation
	ft_putstr_fd("minishell: export: `", 2);
	if (ft_strlen(key))
		ft_putstr_fd(key, 2);
	else
		ft_putstr_fd(tmp, 2);
	// ft_free(tmp, &(data->alloc)); // now safe
	ft_putstr_fd("': not a valid identifier\n", 2);
	(*i)++;
	data->exit_status = 1;
}

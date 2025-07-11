#include "../../include/executor.h"

int	count_commands(t_cmd *cmd)
{
	int count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	get_size(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	convert_path_to_arr_norm(t_env *tmp, char **paths, int *i)
{
	char	*temp;

	while (tmp)
	{
		if (tmp->value)
		{
			temp = ft_strjoin(tmp->name, "=");
			temp = ft_strjoin_free(temp, tmp->value, 1);
			paths[(*i)] = ft_strdup(temp);
			ft_free(temp);
			*i += 1;
		}
		tmp = tmp->next;
	}
}

void	export_not_valid(char *tmp, int *i, char *value, char *key, t_data *data)
{
	tmp = ft_strjoin("=", value);
	ft_putstr_fd("minishell: export: `", 2);
	if (ft_strlen(key))
		ft_putstr_fd(key, 2);
	else
		ft_putstr_fd(tmp, 2);
	ft_free(tmp);
	ft_putstr_fd("': not a valid identifier\n", 2);
	(*i)++;
	data->exit_status = 1;
}


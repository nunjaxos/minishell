#include "../../include/expander.h"

int	export_error_display(t_cmd *cmd, char *key, char *value, int *i, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	if (!check_valid_key(key))
	{
		export_not_valid(tmp, i, value, key);
		return (1);
	}
	if (str_index(cmd->full_cmd[*i], '=')
		&& cmd->full_cmd[*i][str_index(cmd->full_cmd[*i], '=') - 1] == '+'
		&& env_key_exists(data->n_env, key))
		edit_env(data->n_env, key,
			ft_strjoin_free(get_value(key, data->n_env), value, 1));
	else if (str_index(cmd->full_cmd[*i], '=')
		&& cmd->full_cmd[*i][str_index(cmd->full_cmd[*i], '=') - 1] == '+')
		add_env(&data->n_env, ft_strdup(key), ft_strdup(value));
	else if (env_key_exists(data->n_env, key))
		edit_env(data->n_env, key, ft_strdup(value));
	else
		add_env(&data->n_env, ft_strdup(key), ft_strdup(value));
	return (0);
}

int	export_null(int *i, t_cmd *cmd, t_data *data)
{
	char	*key;

	key = ft_strdup(cmd->full_cmd[*i]);
	if (!check_valid_key(key))
	{
		ft_putstr_fd("minishell: export: `", 2);
		if (ft_strlen(key))
			ft_putstr_fd(key, 2);
		else
			ft_putstr_fd("=", 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		*i += 1;
		ft_free(key);
		data->exit_status = 1;
		return (1);
	}
	if (env_key_exists(data->n_env, key))
	{
		if (!get_value(key, data->n_env))
			edit_env(data->n_env, ft_strdup(key), NULL);
	}
	else
		add_env(&data->n_env, ft_strdup(key), NULL);
	return (0);
}

void	export_args_handle(t_cmd *cmd, char *key, char *value, t_data *data)
{
	int	i;

	i = 1;
	while (cmd->full_cmd[i])
	{
		if (ft_strchr(cmd->full_cmd[i], '='))
		{
			value = ft_strchr(cmd->full_cmd[i], '=') + 1;
			key = ft_substr(cmd->full_cmd[i], 0, key_len(cmd->full_cmd[i]));
			if (export_error_display(cmd, key, value, &i, data))
				continue ;
		}
		else if (export_null(&i, cmd, data))
			continue ;
		i++;
		ft_free(key);
	}
	check_for_child(cmd->pid, data->exit_status);
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (ft_strslen(cmd->full_cmd) == 1)
		print_export_list(data->n_env);
	else
		export_args_handle(cmd, key, value, data);
	return (1);
}

void	print_export_list(t_env *env)
{
	t_env	*tmp;
	t_env	*to_free;

	tmp = copy_env_list(env);
	if (!tmp)
		return ;
	sort_env_list(tmp);
	to_free = tmp;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->name, 1);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	free_env(to_free);
}

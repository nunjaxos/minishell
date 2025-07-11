#include "../../include/builtins.h"

void	delete_env(t_env *env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				env = tmp->next;
			ft_free(tmp->name);
			if (tmp->value)
				ft_free(tmp->value);
			ft_free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_cmd *cmd, pid_t pid, t_data *data)
{
	int	i;

	i = 1;
	while (cmd->full_cmd[i])
	{
		if (env_key_exists(data->n_env, cmd->full_cmd[i]))
			delete_env(data->n_env, cmd->full_cmd[i]);
		i++;
	}
	check_for_child(pid, 0);
}

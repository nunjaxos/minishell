#include "../../include/executor.h"

int check_builtins(t_data *data, t_cmd *cmd, pid_t pid)
{
	if (!cmd->full_cmd || !cmd->full_cmd[0])
		return (0);

	if (!ft_strcmp(cmd->full_cmd[0], "echo"))
		return (ft_echo(cmd, pid, data), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "env"))
		return (ft_env(data->n_env), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		return (ft_exit(cmd, pid, data), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		return (ft_unset(cmd, pid, data), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		return (ft_cd(cmd, pid, data), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "pwd"))
		return (ft_pwd(pid, data), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		return (ft_export(cmd, data), 1);
	return (0);
}

int before_child(t_cmd *cmd, t_data *data)
{
	if (!cmd->full_cmd || !cmd->full_cmd[0])
		return (0);
	if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		return (ft_exit(cmd, 1, data), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		return (ft_unset(cmd, 1, data), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		return (ft_cd(cmd, 1, data), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		return (ft_export(cmd, data), 1);
	return (0);
}

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

void	update_last_cmd(t_data *data)
{
	t_cmd	*first_cmd;

	first_cmd = data->head;
	if (!first_cmd || !first_cmd->full_cmd || !first_cmd->full_cmd[0])
		return ;
	if (count_all_commands(&(data->head)) == 1)
	{
		edit_env(data->n_env, "_", ft_strdup(first_cmd->full_cmd[0]));
	}
	else
	{
		edit_env(data->n_env, "_", NULL);
	}
}

int	count_all_commands(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}
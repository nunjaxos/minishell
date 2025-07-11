#include "../../include/executor.h"

int check_builtins(t_data *data, t_cmd *cmd, pid_t pid)
{
	if (!cmd->full_cmd || !cmd->full_cmd[0])
		return (0);

	if (!ft_strcmp(cmd->full_cmd[0], "echo"))
		return (ft_echo(cmd, pid), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "env"))
		return (ft_env(data->n_env, pid), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		return (ft_exit(cmd, pid), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		return (ft_unset(cmd, pid), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		return (ft_cd(cmd, pid), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "pwd"))
		return (ft_pwd(pid), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		return (ft_export(cmd), 1);
	return (0);
}


int before_child(t_cmd *cmd)
{
	if (!cmd->full_cmd || !cmd->full_cmd[0])
		return (0);
	if (!ft_strcmp(cmd->full_cmd[0], "exit"))
		return (ft_exit(cmd, 1), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "unset"))
		return (ft_unset(cmd, 1), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "cd"))
		return (ft_cd(cmd, 1), 1);
	else if (!ft_strcmp(cmd->full_cmd[0], "export"))
		return (ft_export(cmd), 1);
	return (0);
}

#include "../../include/builtins.h"

int	check_for_doubles(char *args)
{
	int	i;

	i = 0;
	if (args[i] == '-')
		i++;
	while (args[i])
	{
		if (args[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(t_cmd *cmd, pid_t pid)
{
	int	i;

	i = 1;
	while ((cmd->full_cmd[i] && (!check_for_doubles(cmd->full_cmd[i]))))
		i++;
	while (cmd->full_cmd[i])
	{
		if (!cmd->full_cmd[i])
			break ;
		ft_putstr_fd(cmd->full_cmd[i], 1);
		if (cmd->full_cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (cmd->full_cmd[1] && !check_for_doubles(cmd->full_cmd[1]))
	{
		check_for_child(pid, 0);
		return ;
	}
	ft_putstr_fd("\n", 1);
	check_for_child(pid, 0);
}

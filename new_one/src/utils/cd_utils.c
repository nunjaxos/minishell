#include "../../include/executor.h"

char	*get_valid_path(t_cmd *cmd, pid_t pid, t_data *data)
{
	char	*path;

	path = cd_error(cmd, pid, data);
	if (!ft_strcmp(cmd->full_cmd[1], "~") || ft_strslen(cmd->full_cmd) == 1)
	{
		path = get_value("HOME", data->n_env);
		if (!path)
		{
			ft_putstr_fd("cd: Error: HOME not set\n", 2);
			data->exit_status = 1;
			check_for_child(pid, 1, data);
			return (NULL);
		}
	}
	return (path);
}

void	update_pwd(t_env *env, t_data *data)
{
	(void)data;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("getcwd");
		exit(1); // or return error
	}
	if (get_value("PWD", env))
	{
		// free(get_value("PWD", env));
		edit_env(env, "PWD", ft_strdup(pwd));
	}
	// free(pwd);
}

void	check_shlvl(t_env *env)
{
	int	shlvl;

	shlvl = ft_atoi_shlvl(get_value("SHLVL", env));
	edit_env(env, "SHLVL", ft_itoa(shlvl + 1));
}

int	ft_atoi_shlvl(char *shlvl)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (shlvl[i])
	{
		if (!ft_isdigit(shlvl[i]))
			return (0);
		nbr = nbr * 10 + (shlvl[i] - '0');
		i++;
	}
	return (nbr);
}
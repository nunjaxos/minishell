#include "../../include/builtins.h"

char	*cd_error(t_cmd *cmd, pid_t pid, t_data *data)
{
	char	*error;

	error = NULL;
	if (ft_strslen(cmd->full_cmd) > 2)
	{
		ft_putstr_fd("cd: Error: too many arguments\n", 2);
		check_for_child(pid, 1);
		return (NULL);
	}
	else if (!ft_strcmp(cmd->full_cmd[1], "-"))
	{
		error = get_value("OLDPWD", data->n_env);
		if (!error)
		{
			ft_putstr_fd("cd: Error: OLDPWD not set\n", 2);
			data->exit_status = 1;
			return (NULL);
		}
		ft_putendl_fd(error, 1);
	}
	return (error);
}

void	change_dir_norm(char *old_pwd, t_data *data)
{
	if (get_value("OLDPWD", data->n_env))
	{
		ft_free(get_value("OLDPWD", data->n_env));
		edit_env(data->n_env, "OLDPWD", old_pwd);
		update_pwd(data->n_env);
	}
	else if (!get_value("OLDPWD", data->n_env))
	{
		edit_env(data->n_env, "OLDPWD", old_pwd);
		update_pwd(data->n_env);
	}
	else
		ft_free(old_pwd);
}

int	change_dir(char *path, pid_t pid, t_data *data)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	add_alloc(old_pwd);
	if (path && path[0] != '\0')
	{
		if (chdir(path))
		{
			perror("cd");
			check_for_child(pid, 1);
			ft_free(old_pwd);
			ft_free(path);
			return (1);
		}
		change_dir_norm(old_pwd, data);
	}
	else
		ft_free(old_pwd);
	return (0);
}

int	ft_cd(t_cmd *cmd, pid_t pid, t_data *data)
{
	char	*path_no_free;
	char	*path;

	path_no_free = get_valid_path(cmd, pid);
	if (!path_no_free)
	{
		if (!ft_strcmp(cmd->full_cmd[1], "-") || !ft_strcmp(cmd->full_cmd[1], "~"))
			return (0);
		path = ft_strdup(cmd->full_cmd[1]);
	}
	if (path_no_free)
	{
		if (change_dir(path_no_free, pid, data))
			return (1);
	}
	else if (path)
	{
		if (change_dir(path, pid, data))
			return (1);
		ft_free(path);
	}
	env_update(data->n_env);
	return (0);
}

#include "../../include/executor.h"

char	*cd_error(t_cmd *cmd, pid_t pid, t_data *data)
{
	char	*error = NULL;

	if (ft_strslen(cmd->full_cmd) > 2)
	{
		ft_putstr_fd("cd: Error: too many arguments\n", 2);
		check_for_child(pid, 1, data);
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
		ft_free(get_value("OLDPWD", data->n_env), &(data->alloc));
		edit_env(data->n_env, "OLDPWD", old_pwd);
		update_pwd(data->n_env);
	}
	else
	{
		edit_env(data->n_env, "OLDPWD", old_pwd);
		update_pwd(data->n_env);
	}
}

int	change_dir(char *path, pid_t pid, t_data *data)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	add_alloc(old_pwd, &data->alloc);

	if (path && path[0] != '\0')
	{
		if (chdir(path))
		{
			perror("cd");
			check_for_child(pid, 1, data);
			ft_free(old_pwd, &(data->alloc));
			ft_free(path, &(data->alloc));
			return (1);
		}
		change_dir_norm(old_pwd, data);
	}
	else
		ft_free(old_pwd, &(data->alloc));
	return (0);
}

int	ft_cd(t_cmd *cmd, pid_t pid, t_data *data)
{
	char	*path_no_free = NULL;
	char	*path = NULL;

	path_no_free = get_valid_path(cmd, pid, data);
	if (!path_no_free)
	{
		if (!ft_strcmp(cmd->full_cmd[1], "-") || !ft_strcmp(cmd->full_cmd[1], "~"))
			return (0);
		path = ft_strdup(cmd->full_cmd[1]);
		add_alloc(path, &data->alloc);
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
		ft_free(path, &(data->alloc));
	}
	env_update(data->n_env);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_cmd	cmd;
	char	**cmd_args;

	// Step 1: Initialize data
	ft_bzero(&data, sizeof(t_data));
	data.alloc = NULL;

	// ✅ Corrected: init_env_list fills data.n_env
	init_env_list(envp, &data.n_env);

	// Step 2: Simulate `cd` command
	cmd.full_cmd = NULL;
	cmd.in_file = STDIN_FILENO;
	cmd.out_file = STDOUT_FILENO;

	if (argc > 1)
	{
		cmd_args = malloc(sizeof(char *) * argc);
		for (int i = 1; i < argc; i++)
			cmd_args[i - 1] = ft_strdup(argv[i]);
		cmd_args[argc - 1] = NULL;
		cmd.full_cmd = cmd_args;
	}
	else
	{
		cmd_args = malloc(sizeof(char *) * 2);
		cmd_args[0] = ft_strdup("cd");
		cmd_args[1] = NULL;
		cmd.full_cmd = cmd_args;
	}

	// Step 3: Call cd
	ft_cd(&cmd, 0, &data);

	// Step 4: Print result
	char *cwd = getcwd(NULL, 0);
	printf("Current Directory: %s\n", cwd);
	free(cwd);

	// Free cmd args
	for (int i = 0; cmd.full_cmd[i]; i++)
		free(cmd.full_cmd[i]);
	free(cmd.full_cmd);

	// Free env list
	free_env_list(data.n_env);

	// Free all tracked allocations
	garbage_removal(&data.alloc);

	return (0);
}

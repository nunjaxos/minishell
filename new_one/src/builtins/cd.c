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
		// free(get_value("OLDPWD", data->n_env));
		edit_env(data->n_env, "OLDPWD", old_pwd);
		update_pwd(data->n_env, data);
	}
	else
	{
		edit_env(data->n_env, "OLDPWD", old_pwd);
		update_pwd(data->n_env, data);
	}
}

int	change_dir(char *path, pid_t pid, t_data *data)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("getcwd");
		exit(1); // or return error
	}
	if (path && path[0] != '\0')
	{
		if (chdir(path))
		{
			perror("cd");
			check_for_child(pid, 1, data);
			// free(old_pwd);
			// free(path);
			return (1);
		}
		change_dir_norm(old_pwd, data);
	}
	// else
	// 	free(old_pwd);
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
		path = ft_strdup(cmd->full_cmd[1]); // allocates memory already
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
		// free(path); // properly free it
	}
	env_update(data->n_env, data);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_data	data;
// 	t_cmd	cmd;
// 	// char	*args1[] = {"cd", "/", NULL}; // ✅ Test 1: go to root
// 	// char *args2[] = {"cd", "-", NULL}; // ✅ Test 2: go to OLDPWD
// 	char *args3[] = {"cd", "~", NULL}; // ✅ Test 3: go to HOME
// 	// char *args4[] = {"cd", "/invalid", NULL}; // ❌ Test 4: error path
// 	// char *args5[] = {"cd", "dir1", "dir2", NULL}; // ❌ Test 5: too many args

// 	// ✅ Clean init
// 	ft_bzero(&data, sizeof(t_data));
// 	init_env_list(envp, &data);

// 	cmd.full_cmd = args3; // change here to test other cases
// 	cmd.pid = 0;

// 	printf("=== ENV BEFORE CD ===\n");
// 	print_export_list(data.n_env, &data);

// 	if (ft_cd(&cmd, cmd.pid, &data) == 0)
// 		printf("cd success ✅\n");
// 	else
// 		printf("cd failed ❌\n");

// 	printf("=== ENV AFTER CD ===\n");
// 	print_export_list(data.n_env, &data);

// 	// garbage_removal(&data.alloc);
// 	return (0);
// }

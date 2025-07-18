#include "../../include/executor.h"

int	execute_commands(t_data *data)
{
	t_cmd	*cmd = data->head;
	int		cmd_count = count_commands(cmd);

	update_last_cmd(data);

	if (cmd_count == 1)
		exec_one_command(cmd, data);
	else
		create_pipe(cmd, cmd_count, data);

	return (0);
}
		//test

void free_char_array(char **arr)
{
    int i = 0;
    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char *find_full_path(char *cmd, t_env *env)
{
    char *path_env = NULL;
    char **paths = NULL;
    char *full_path = NULL;
    struct stat sb;
    int i = 0;

    // Find PATH value in env linked list
    while (env)
    {
        if (!strcmp(env->name, "PATH"))
        {
            path_env = env->value;
            break;
        }
        env = env->next;
    }
    if (!path_env)
        return NULL;

    // Split PATH by ':'
    paths = ft_split(path_env, ':');
    if (!paths)
        return NULL;

    // Try each path + "/" + cmd
    while (paths[i])
    {
        full_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin_free(full_path, cmd, 1, get_data()); // custom function to concat and free first param
        if (stat(full_path, &sb) == 0 && (sb.st_mode & S_IXUSR))
        {
            // Free split array
            free_char_array(paths);
            return full_path; // Found executable
        }
        free(full_path);
        full_path = NULL;
        i++;
    }
    free_char_array(paths);
    return NULL;
}

t_env	*find_env(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_data	*data;
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	// Allocate and init t_data
	data = malloc(sizeof(t_data));
	ft_bzero(data, sizeof(t_data));
	init_env_list(envp, data); // your own function to init env list

	// Create cmd1: echo hello
	cmd1 = malloc(sizeof(t_cmd));
	ft_bzero(cmd1, sizeof(t_cmd));
	cmd1->full_cmd = malloc(sizeof(char *) * 3);
	cmd1->full_cmd[0] = ft_strdup("echo");
	cmd1->full_cmd[1] = ft_strdup("hello");
	cmd1->full_cmd[2] = NULL;
	cmd1->in_file = 0;
	cmd1->out_file = 1;
	cmd1->next = NULL;

	// Create cmd2: grep h
	cmd2 = malloc(sizeof(t_cmd));
	ft_bzero(cmd2, sizeof(t_cmd));
	cmd2->full_cmd = malloc(sizeof(char *) * 3);
	cmd2->full_cmd[0] = ft_strdup("grep");
	cmd2->full_cmd[1] = ft_strdup("h");
	cmd2->full_cmd[2] = NULL;
	cmd2->in_file = 0;
	cmd2->out_file = 1;
	cmd2->next = NULL;

	// Link them for piping
	cmd1->next = cmd2;

	// Setup data
	data->head = cmd1;

	// Call the executor
	execute_commands(data);

	// Cleanup (if needed)
	return (0);
}

t_data	*get_data(void)
{
	static t_data	*data = NULL;

	if (!data)
		data = malloc(sizeof(t_data));
	return (data);
}
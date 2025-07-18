#include "../../include/executor.h"

void	delete_env(t_env **env, char *key, t_data *data)
{
	(void)data;
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, key))
		{
			printf("Unsetting key: %s\n", key);
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			// ft_free(tmp->name, &(data->alloc));
			// if (tmp->value)
			// 	ft_free(tmp->value, &(data->alloc));
			// ft_free(tmp, &(data->alloc));
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_cmd *cmd, pid_t pid, t_data *data)
{
	(void)data;
	int	i;

	i = 1;
	while (cmd->full_cmd[i])
	{
		if (env_name_exists(data->n_env, cmd->full_cmd[i]))
			delete_env(&data->n_env, cmd->full_cmd[i], data);
		i++;
	}
	printf("Finished unset loop\n");
	check_for_child(pid, 0, data);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;

// 	t_data	*data;
// 	t_cmd	cmd;

// 	data = malloc(sizeof(t_data));            // ✅ allocate memory
// 	if (!data)
// 		return (1);                          // handle allocation failure
// 	ft_bzero(data, sizeof(t_data));          // ✅ zero out actual structure

// 	// Now safe to use
// 	init_env_list(envp, data);

// 	printf("=== ENV BEFORE UNSET ===\n");
// 	print_export_list(data->n_env, data);
// 	printf("yppppp\n");
// 	char *unset1[] = {"unset", "PATH", NULL};
// 	cmd.full_cmd = unset1;
// 	cmd.pid = 0;
// 	ft_unset(&cmd, cmd.pid, data);
// 	printf("nooo\n");
// 	char *unset2[] = {"unset", "HOME", NULL};
// 	cmd.full_cmd = unset2;
// 	ft_unset(&cmd, cmd.pid, data);

// 	char *unset3[] = {"unset", "NOT_PRESENT", NULL};
// 	cmd.full_cmd = unset3;
// 	ft_unset(&cmd, cmd.pid, data);

// 	printf("\n=== ENV AFTER UNSET ===\n");
// 	print_export_list(data->n_env, data);

// 	// free_env(data->n_env, data);
// 	// garbage_removal(&data->alloc);
// 	// free(data);  // ✅ don't forget to free the struct itself

// 	return 0;
// }

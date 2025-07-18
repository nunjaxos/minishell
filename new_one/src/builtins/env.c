#include "../../include/executor.h"

t_env *create_env_node(const char *env, t_data *data)
{
	t_env *node;

	node = ft_malloc(sizeof(t_env), &data->alloc);
	if (!node)
		return (NULL);
	char *sep = strchr(env, '=');
	if (!sep)
		return (NULL); // Don't free node — it’s tracked
	node->name = ft_strdup_track(env, sep - env, &data->alloc);
	if (!node->name)
		return (NULL);
	node->value = ft_strdup_track(sep + 1, -1, &data->alloc); // -1 = till null
	if (!node->value)
		return (NULL);
	node->next = NULL;
	return node;
}


void add_env_back(t_env **lst, t_env *new_node)
{
	if (!lst || !new_node)
		return;
	if (!*lst)
	{
		*lst = new_node;
		return;
	}
	t_env *temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	init_env_list(char **envp, t_data *data)
{
	int		i = 0;
	t_env	*node;

	while (envp[i])
	{
		node = create_env_node(envp[i], data);
		if (node)
			add_env_back(&data->n_env, node);
		i++;
	}
}

void free_env_list(t_env *env)
{
	t_env *tmp;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env *env_list = NULL;

// 	(void)argc;
// 	(void)argv;

// 	init_env_list(envp, &env_list);
// 	ft_env(env_list);
// 	free_env_list(env_list);
// 	return (0);
// }

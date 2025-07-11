#include "../../include/builtins.h"

t_env *create_env_node(const char *env)
{
	t_env *node;
	
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	char *sep = strchr(env, '=');
	if (!sep)
		return (free(node), NULL);
	node->name = ft_strndup(env, sep - env);
	if (!node->name)
		return (free(node), NULL);
	node->value = strdup(sep + 1);
	if (!node->value)
		return (free(node->name), free(node), NULL);
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

void init_env_list(char **envp, t_data *data)
{
	int i = 0;
	t_env *node;

	data->n_env = NULL;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
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


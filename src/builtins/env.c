#include "../../include/executor.h"

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

void init_env_list(char **envp, t_env **env_list)
{
	int i = 0;
	while (envp[i])
	{
		t_env *node = create_env_node(envp[i]);
		if (node)
			add_env_back(env_list, node);
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

#include "../../include/executor.h"

t_env *copy_env_list(t_env *env, t_data *data)
{
	(void)data;
	t_env *tmp = env;
	t_env *new;
	t_env *head = NULL;
	t_env *last = NULL;

	while (tmp)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return NULL;

		new->name = ft_strdup(tmp->name);
		
		if (tmp->value)
			new->value = ft_strdup(tmp->value);
		else
			new->value = NULL;
		new->next = NULL;
		if (!head)
		{
			head = new;
		}
		else
		{
			last->next = new;
		}
		last = new;
		tmp = tmp->next;
	}
	return head;
}


void	sort_env_list(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*temp;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->name, tmp2->name) > 0)
			{
				temp = tmp->name;
				tmp->name = tmp2->name;
				tmp2->name = temp;
				temp = tmp->value;
				tmp->value = tmp2->value;
				tmp2->value = temp;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void free_env(t_env *head, t_data *data)
{
	t_env *tmp;

	(void)data; // suppress unused warning if not using alloc
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

int	env_name_exists(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	edit_env(t_env *head, char *key, char *new_value)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp(current->name, key))
		{
			if (current->value)
				free(current->value); // free the old value
			current->value = new_value;
			return ;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	// If key not found, add it at the end
	t_env *new_node = ft_calloc(1, sizeof(t_env));
	new_node->name = ft_strdup(key);
	new_node->value = new_value;
	new_node->next = NULL;
	current->next = new_node;
}

void	add_env(t_env **head, char *name, char *value, t_data *data)
{
	(void)data;
	t_env	*new;
	t_env	*last;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free_env(*head, data);
		return ;
	}
	new->name = name;
	new->value = value;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	env_update(t_env *env, t_data *data)
{
	if (!get_value("OLDPWD", env))
		add_env(&env, "OLDPWD", NULL, data);
	check_shlvl(env);
}
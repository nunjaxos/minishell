#include "../../include/builtins.h"

int	check_for_child(pid_t pid, int exit_stat, t_data *data) 
{
	if (pid == 0)
	{
		data->exit_status = exit_stat;
		free_parser(data);
		exit(exit_stat);
	}
	else
		data->exit_status = exit_stat;
	return (0);
}


t_env	*copy_env_list(t_env *env)
{
	t_env	*tmp;
	t_env	*new;
	t_env	*head;

	tmp = env;
	head = NULL;
	while (tmp)
	{
		new = ft_malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		new->name = ft_strdup(tmp->name);
		new->value = ft_strdup(tmp->value);
		new->next = NULL;
		if (!head)
			head = new;
		else
		{
			new->next = head;
			head = new;
		}
		tmp = tmp->next;
	}
	return (head);
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

int	check_valid_name(char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[i]) && name[i] != '_')
		return (0);
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
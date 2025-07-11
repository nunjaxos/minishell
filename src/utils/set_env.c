/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:13:40 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/28 18:48:22 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

t_env	*set_env(char **env)
{
	t_env	*head;
	t_env	*new;
	t_env	*last;
	int		i;

	if (!env || !env[0])
		return (NULL);
	i = 0;
	head = NULL;
	while (env[i])
	{
		new = ft_malloc(sizeof(t_env));
		if (!new)
			return (free_env(head), NULL);
		if (copy_env(env[i], new))
			return (free_env(head), NULL);
		new->next = NULL;
		if (!head)
			head = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return (head);
}

int	copy_env(char *env, t_env *new)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (env[i] && env[i] != '=')
		i++;
	new->name = ft_malloc(sizeof(char) * (i + 1));
	if (!new->name)
		return (1);
	new->value = ft_malloc(sizeof(char) * (ft_strlen(env) - i));
	if (!new->value)
		return (ft_free(new->name), 1);
	while (++j < i)
		new->name[j] = env[j];
	new->name[i++] = '\0';
	j = 0;
	while (env[i])
		new->value[j++] = env[i++];
	new->value[j] = '\0';
	return (0);
}

void	free_env(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current)
	{
		next = current->next;
		if (current->name)
		{
			ft_free(current->name);
			current->name = NULL;
		}
		if (current->value)
		{
			ft_free(current->value);
			current->value = NULL;
		}
		if (current)
		{
			ft_free(current);
			current = NULL;
		}
		current = next;
	}
	current = NULL;
}

void	add_env(t_env **head, char *name, char *value)
{
	t_env	*new;
	t_env	*last;

	new = ft_malloc(sizeof(t_env));
	if (!new)
	{
		free_env(*head);
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

void	edit_env(t_env *head, char *name, char *new_value)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
		{
			current->value = new_value;
			return ;
		}
		current = current->next;
	}
}

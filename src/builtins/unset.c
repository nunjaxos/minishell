/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 21:46:41 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/09/02 19:07:50 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	delete_env(t_env *env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				env = tmp->next;
			ft_free(tmp->key);
			if (tmp->value)
				ft_free(tmp->value);
			ft_free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	ft_unset(t_cmd *cmd, pid_t pid)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (env_key_exists(get_parser()->env, cmd->args[i]))
			delete_env(get_parser()->env, cmd->args[i]);
		i++;
	}
	check_for_child(pid, 0);
}

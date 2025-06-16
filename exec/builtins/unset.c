/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:26:37 by abhmidat          #+#    #+#             */
/*   Updated: 2025/06/15 10:28:37 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_env_var(t_env **env_list, const char *name)
{
    t_env *curr;
    t_env *prev;

	curr = *env_list;
	prev = NULL;
    while (curr)
    {
        if (strcmp(curr->name, name) == 0)
        {
            if (prev)
                prev->next = curr->next;
            else
                *env_list = curr->next;

            free(curr->name);
            free(curr->content);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int unset(char **args)
{
    int i;

	i = 1;
    if (!args[1])
        return 0;

    while (args[i])
    {
        remove_env_var(&g_envp, args[i]);
		i++;
    }
    return 0;
}

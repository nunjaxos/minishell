/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:21:35 by abhmidat          #+#    #+#             */
/*   Updated: 2025/06/15 11:17:19 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *find_env(t_env *env, const char *name)
{
    while (env)
    {
        if (strcmp(env->name, name) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}

void update_env(t_env **env, const char *name, const char *value)
{
    t_env *node = find_env(*env, name);

    if (node)
    {
        free(node->content);
        node->content = strdup(value);
    }
    else
    {
        t_env *new_node = malloc(sizeof(t_env));
        if (!new_node)
            return;
        new_node->name = strdup(name);
        new_node->content = strdup(value);
        new_node->next = NULL;
        add_env_back(env, new_node);
    }
}


char *ft_strndup(const char *s, size_t n)
{
    char *dup;
	size_t i;
	
	dup = malloc(n + 1);
    if (!dup)
        return NULL;
    i = 0;
    while (i < n && s[i] != '\0') {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return dup;
}

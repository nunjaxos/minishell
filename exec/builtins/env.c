/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:57:22 by abhmidat          #+#    #+#             */
/*   Updated: 2025/06/15 11:40:33 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_env *g_envp = NULL;

t_env *create_env_node(const char *env)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	char *sep = strchr(env, '=');
	if (!sep)
		return (free(node), NULL);
	node->name = ft_strndup(env, sep - env);
	if (!node->name)
    	return (free(node), NULL);
	node->content = strdup(sep + 1);
	if (!node->content)
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

void init_env_list(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		t_env *node = create_env_node(envp[i]);
		if (node)
			add_env_back(&g_envp, node);
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
        free(tmp->content);
        free(tmp);
    }
}

// int main(int ac, char **av, char **envp)
// {
// 	(void)ac;
// 	(void)av;
// 	init_env_list(envp);
	
// 	t_env *tmp = g_envp;
// 	while (tmp)
// 	{
// 		printf("%s=%s\n", tmp->name, tmp->content);
// 		tmp = tmp->next;
// 	}
// 	free_env_list(g_envp);
// 	return 0;
// }

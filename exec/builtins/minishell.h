/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:26:48 by abhmidat          #+#    #+#             */
/*   Updated: 2025/06/15 11:38:45 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../../libft/libft.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

extern t_env	*g_envp;

		//utils
t_env *find_env(t_env *env, const char *name);
void update_env(t_env **env, const char *name, const char *value);
char *ft_strndup(const char *s, size_t n);
void add_env_back(t_env **lst, t_env *new_node);

#endif
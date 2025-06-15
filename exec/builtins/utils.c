/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:21:35 by abhmidat          #+#    #+#             */
/*   Updated: 2025/06/13 14:22:26 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

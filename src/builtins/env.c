/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 18:40:45 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/08/21 22:11:10 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	ft_env(t_env *env, pid_t pid)
{
	int		i;
	char	**str;

	i = 0;
	str = convert_path_to_array(env);
	while (str[i])
	{
		ft_putendl_fd(str[i], 1);
		i++;
	}
	free_char_array(str);
	check_for_child(pid, 0);
}

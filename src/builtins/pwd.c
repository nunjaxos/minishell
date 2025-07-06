/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:31:41 by ybouaoud          #+#    #+#             */
/*   Updated: 2024/08/23 20:40:24 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

void	ft_pwd(pid_t pid)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	add_alloc(pwd);
	ft_putendl_fd(pwd, 1);
	ft_free(pwd);
	check_for_child(pid, 0);
}

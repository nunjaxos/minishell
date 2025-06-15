/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 12:27:05 by abhmidat          #+#    #+#             */
/*   Updated: 2025/06/11 14:56:13 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nl_param(char *param)
{
	int	i;

	if (!ft_strcmp(param, "-n"))
		return (1);
	if (param[0] == '-' && param[1] == 'n')
	{
		i = 1;
		while (param[++i])
		{
			if (param[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	echo(int ac, char **av)
{
	int	i;
	int	nl;
	int	first;

	nl = 1;
	first = 1;
	i = 0;
	while (av[++i] && nl_param(av[i]))
		nl = 0;
	while (i < ac)
	{
		if (!first)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(av[i], 1);
		if (first)
			first = 0;
		++i;
	}
	if (ac >= 1 && nl)
		ft_putchar_fd('\n', 1);
	return (0);
}

int main(int argc, char **argv)
{
    echo(argc, argv);
    return 0;
}

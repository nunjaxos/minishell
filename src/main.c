/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:10:20 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/30 14:58:29 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_sigchild;

int	main(int ac, char **av, char **env)
{
	t_parser	*parser;

	g_sigchild = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (ac != 1 || av[1])
	{
		write(2, "Error: No Args Needed\n", 23);
		exit(1);
	}
	parser = readfrom(env);
	if (!parser)
		exit(1);
	return (0);
}

t_parser	*get_parser(void)
{
	static t_parser	*parser = NULL;

	if (!parser)
		parser = malloc(sizeof(t_parser));
	return (parser);
}

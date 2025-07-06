/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:41:43 by amouhand          #+#    #+#             */
/*   Updated: 2024/09/05 11:39:02 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/signals.h"

void	sigint_handler(int signo)
{
	get_parser()->exit_status = 130;
	if (signo == SIGINT && g_sigchild)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sigchild = 0;
	}
	else
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int signo)
{
	get_parser()->exit_status = 131;
	if (signo == SIGQUIT && g_sigchild)
	{
		printf("Quit (core dumped)\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		g_sigchild = 0;
	}
	else
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

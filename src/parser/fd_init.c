/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:08:11 by amouhand          #+#    #+#             */
/*   Updated: 2024/09/01 07:57:32 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	fd_init(t_cmd **cmd)
{
	int				i;
	t_redirection	*redir;
	int				fail_flag;

	i = -1;
	while (cmd[++i])
	{
		cmd[i]->in_fd = 0;
		cmd[i]->out_fd = 1;
		redir = cmd[i]->redirections;
		while (redir)
		{
			if (redir->redir->type == INPUT)
				fail_flag = close_and_open_input(cmd[i], redir);
			else if (redir->redir->type == APPEND)
				fail_flag = close_and_open_append(cmd[i], redir);
			else if (redir->redir->type == REDIR)
				fail_flag = close_and_open_output(cmd[i], redir);
			else if (redir->redir->type == HEREDOC)
				fail_flag = heredoc_fd(cmd[i], redir);
			if (fail_flag)
				break ;
			redir = redir->next;
		}
	}
}

void	add_redirection(t_cmd *cmd, t_token *redir_token, char *arg)
{
	t_redirection	*new_redir;
	t_redirection	*current;

	new_redir = ft_malloc(sizeof(t_redirection));
	if (!new_redir)
		return ;
	new_redir->redir = redir_token;
	new_redir->arg = ft_strdup(arg);
	new_redir->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

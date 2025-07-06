/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:59:15 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/30 19:34:11 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	heredoc_fd(t_cmd *cmd, t_redirection *redir)
{
	if (cmd->in_fd != 0 && cmd->in_fd != -1)
		close(cmd->in_fd);
	cmd->in_fd = redir->fd;
	return (0);
}

int	close_and_open_input(t_cmd *cmd, t_redirection *redir)
{
	if (cmd->in_fd != 0 && cmd->in_fd != -1)
		close(cmd->in_fd);
	redir->fd = open(redir->arg, O_RDONLY);
	if (redir->fd == -1)
		return (1);
	cmd->in_fd = redir->fd;
	return (0);
}

int	close_and_open_output(t_cmd *cmd, t_redirection *redir)
{
	if (cmd->out_fd != 1 && cmd->out_fd != -1)
		close(cmd->out_fd);
	redir->fd = open(redir->arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
		return (1);
	cmd->out_fd = redir->fd;
	return (0);
}

int	close_and_open_append(t_cmd *cmd, t_redirection *redir)
{
	if (cmd->out_fd != 1 && cmd->out_fd != -1)
		close(cmd->out_fd);
	redir->fd = open(redir->arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir->fd == -1)
		return (1);
	cmd->out_fd = redir->fd;
	return (0);
}

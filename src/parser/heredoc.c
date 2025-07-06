/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:13:33 by amouhand          #+#    #+#             */
/*   Updated: 2024/09/05 12:02:33 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_configuring(t_cmd **cmd)
{
	t_redirection	*redir;
	int				i;

	i = 0;
	while (cmd[i])
	{
		redir = cmd[i]->redirections;
		while (redir)
		{
			if (redir->redir->type == HEREDOC)
			{
				if (open_heredoc(redir))
					return (1);
			}
			if (get_parser()->heredoc_abort)
				return (1);
			redir = redir->next;
		}
		i++;
	}
	return (0);
}

int	handle_parent_process(int fd, char *name, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		get_parser()->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		get_parser()->exit_status = WTERMSIG(status) + 128;
		if (get_parser()->exit_status == 130)
		{
			close(fd);
			unlink(name);
			ft_free(name);
			get_parser()->heredoc_abort = 1;
			return (1);
		}
	}
	g_sigchild = 0;
	return (0);
}

int	finalize_heredoc(t_redirection *redir, char *name)
{
	char	*tmp;

	redir->fd = open(name, O_RDONLY);
	unlink(name);
	ft_free(name);
	tmp = quotes_in_heredoc(redir->arg);
	ft_free(redir->arg);
	redir->arg = ft_strdup(tmp);
	ft_free(tmp);
	if (redir->fd == -1)
		return (1);
	return (0);
}

int	open_heredoc(t_redirection *redir)
{
	char	*name;
	int		fd;
	pid_t	pid;

	name = generate_temp_filename(redir->arg);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (ft_free(name), 1);
	pid = fork();
	g_sigchild = 1;
	if (pid == 0)
		process_heredoc_lines(fd, redir);
	else if (pid == -1)
		return (1);
	else if (pid > 0)
	{
		if (handle_parent_process(fd, name, pid))
			return (1);
	}
	close(fd);
	return (finalize_heredoc(redir, name));
}

void	process_heredoc_lines(int fd, t_redirection *redir)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		heredoc_signals();
		line = readline("> ");
		if (!line)
			break ;
		add_alloc(line);
		tmp = quotes_in_heredoc(redir->arg);
		if (!ft_strcmp(line, tmp))
		{
			ft_free(line);
			ft_free(tmp);
			break ;
		}
		ft_free(tmp);
		line = expand_heredoc(line, check_for_quotes(redir->arg));
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		ft_free(line);
	}
	free_parser(get_parser());
	exit(0);
}

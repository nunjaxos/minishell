/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:37:35 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/13 18:26:14 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	checking_parsing(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!current->next)
				return (parsing_error("|", 2), 1);
			else if (current == head)
				return (parsing_error("|", 2), 1);
			else if (current->next->type == PIPE)
				return (parsing_error("|", 2), 1);
		}
		else if (current->type == REDIR || current->type == HEREDOC
			|| current->type == INPUT || current->type == APPEND)
		{
			if (!current->next)
				return (parsing_error("newline", 2), 1);
			else if (current->next->type != WORD)
				return (parsing_error(current->next->value, 2), 1);
		}
		current = current->next;
	}
	return (0);
}

void	parsing_error(char *message, int status)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("'\n", 2);
	get_parser()->exit_status = status;
}

void	path_check(t_cmd *cmd, char **paths)
{
	if (if_builtin(cmd->args[0]))
		cmd->access = IS_BUILTIN;
	else if (!cmd->args[0])
		cmd->access = NULL_CMD;
	else if (!ft_strlen(cmd->args[0]))
		cmd->access = CMD_NOT_FOUND;
	else if (test_path(paths, cmd))
		;
	else
		test_binaries(cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 12:02:55 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/30 18:27:32 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	process_token(t_token **current, t_token **before, t_cmd **cmd, int i)
{
	t_token	*redirect;

	while (*current && (*current)->type != PIPE)
	{
		if ((*current)->type == REDIR || (*current)->type == PIPE
			|| (*current)->type == INPUT || (*current)->type == APPEND
			|| (*current)->type == HEREDOC)
		{
			redirect = *current;
			*before = *current;
			*current = (*current)->next;
			if (*current && (*current)->type == WORD)
				add_redirection(cmd[i], redirect, (*current)->value);
		}
		else
		{
			*before = *current;
			*current = (*current)->next;
		}
	}
}

int	count_args(t_token *start)
{
	int		count;
	t_token	*before;

	count = 0;
	before = NULL;
	while (start && start->type != PIPE)
	{
		if (start->type == WORD)
		{
			if (!before || (before->type != REDIR && before->type != INPUT
					&& before->type != APPEND && before->type != HEREDOC))
				count++;
		}
		before = start;
		start = start->next;
	}
	return (count);
}

void	fill_args(t_token *start, t_token *end, t_cmd *cmd)
{
	int		j;
	t_token	*before_tmp;

	j = 0;
	before_tmp = start;
	while (start && start != end && start->type != PIPE)
	{
		if (start->type == WORD && (before_tmp->type != REDIR
				&& before_tmp->type != INPUT && before_tmp->type != APPEND
				&& before_tmp->type != HEREDOC))
		{
			cmd->args[j] = ft_strdup(start->value);
			j++;
		}
		before_tmp = start;
		start = start->next;
	}
	cmd->args[j] = NULL;
}

int	count_pipes(t_token *head)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

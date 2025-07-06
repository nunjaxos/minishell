/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:29:40 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/25 18:14:26 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_cmd	**parse_cmd(t_token *head)
{
	t_cmd	**cmd;
	int		count;

	count = count_pipes(head);
	cmd = ft_malloc(sizeof(t_cmd *) * (count + 2));
	if (!cmd)
		return (NULL);
	allocate_cmd(cmd, head);
	return (cmd);
}

void	allocate_cmd(t_cmd **cmd, t_token *head)
{
	int		i;
	t_token	*current;
	t_token	*before;
	t_token	*tmp_token;

	i = 0;
	current = head;
	while (current)
	{
		tmp_token = current;
		initialize_cmd(cmd, tmp_token, i);
		process_token(&current, &before, cmd, i);
		if (current && current->type == PIPE)
		{
			before = current;
			current = current->next;
		}
		i++;
	}
	cmd[i] = NULL;
}

void	initialize_cmd(t_cmd **cmd, t_token *current, int i)
{
	t_token	*tmp_token;
	int		count;

	cmd[i] = ft_malloc(sizeof(t_cmd));
	if (!cmd[i])
		return ;
	cmd[i]->redirections = NULL;
	tmp_token = current;
	count = count_args(tmp_token);
	cmd[i]->args = ft_malloc(sizeof(char *) * (count + 1));
	if (!cmd[i]->args)
		return ;
	cmd[i]->count = count;
	if (!cmd[i]->args)
		return ;
	fill_args(tmp_token, NULL, cmd[i]);
}

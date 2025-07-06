/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:38:56 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/30 17:59:09 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

int	expander(t_cmd **cmds)
{
	int				i;
	t_redirection	*re;

	i = 0;
	while (cmds[i])
	{
		re = cmds[i]->redirections;
		if (cmds[i])
			expand_command(cmds[i]);
		if (cmds[i]->redirections)
		{
			if (expand_redirections(re))
				return (1);
		}
		i++;
	}
	return (0);
}

char	*expand_env(char *arg, int flag)
{
	char	*before;
	char	*result;

	before = process_before(arg, &flag);
	result = process_expand_and_after(arg, before, flag);
	return (ft_free(arg), result);
}

char	*process_before(char *arg, int *flag)
{
	char	*before;
	int		tmp;

	tmp = *flag;
	before = get_before(arg);
	before = remove_quotes(before, flag);
	if (ft_strlen(before))
		expand_list_process(before, tmp, 0);
	return (before);
}

char	*process_expand_and_after(char *arg, char *before, int flag)
{
	char	*expand;
	char	*after;
	char	*result;
	int		tmp;

	result = ft_strdup(arg);
	expand = ft_strchr(arg, '$') + 1;
	if (expand)
	{
		expand = get_expand(expand, flag);
		if (expand)
			expand_list_process(expand, flag, 1);
		after = get_after(arg);
		if (ft_strchr(after, '$'))
			after = expand_env(after, flag);
		else
		{
			tmp = flag;
			after = remove_quotes(after, &flag);
			if (ft_strlen(after))
				expand_list_process(after, tmp, 0);
		}
		result = joining(result, before, expand, after);
	}
	return (result);
}

void	expand_command(t_cmd *cmd)
{
	int	len;
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (find_expand(cmd->args[i], 0))
		{
			cmd->args[i] = expand_env(cmd->args[i], 0);
			len = ft_strlen(cmd->args[i]);
			if (len && cmd->args[i][len - 1] != '$')
				cmd->args = expand_space(cmd, &i, joining_expand_list(cmd));
			else
			{
				if (!ft_strlen(cmd->args[i]))
				{
					cmd->args = replace_null(cmd->args, i);
					cmd->count--;
					i--;
				}
				free_expand_list();
			}
		}
		i++;
	}
}

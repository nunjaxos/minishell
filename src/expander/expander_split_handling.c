/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split_handling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:17:05 by amouhand          #+#    #+#             */
/*   Updated: 2024/09/01 08:03:19 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

int	expand_redirections(t_redirection *re)
{
	char	*tmp;

	while (re)
	{
		if (re->redir->type != HEREDOC && find_expand(re->arg, 0))
		{
			tmp = ft_strdup(re->arg);
			re->arg = expand_env(re->arg, 0);
			if (space_available(re->arg) || !ft_strlen(re->arg))
				return (ambiguos_redirect(tmp), 1);
		}
		re = re->next;
	}
	return (0);
}

char	**replace_null(char **arr, int index)
{
	char	**result;
	int		i;
	int		j;
	int		count;

	if (!arr)
		return (NULL);
	count = count_char_array(arr);
	if (index < 0 || index >= count)
		return (arr);
	result = ft_malloc(sizeof(char *) * (count_char_array(arr)));
	i = -1;
	j = 0;
	while (arr[++i])
	{
		if (i != index)
		{
			result[j] = ft_strdup(arr[i]);
			if (!result[j])
				return (free_char_array(arr), NULL);
			j++;
		}
	}
	result[j] = NULL;
	return (free_char_array(arr), result);
}

char	**expand_space(t_cmd *cmd, int *j, char **expanded)
{
	char	**result;
	int		i;
	int		k;
	int		result_index;

	i = 0;
	k = 0;
	result_index = 0;
	result = ft_malloc(sizeof(char *) * (count_char_array(expanded)
				+ count_char_array(cmd->args)));
	while (cmd->args[i])
	{
		while (i == *j && expanded[k])
			result[result_index++] = ft_strdup(expanded[k++]);
		if (i != *j)
			result[result_index++] = ft_strdup(cmd->args[i]);
		i++;
	}
	result[result_index] = NULL;
	*j = *j + count_char_array(expanded) - 1;
	return (free_char_array(expanded), free_char_array(cmd->args), result);
}

int	find_split_flag(t_expand *expand, t_expand *prev)
{
	int			flag;

	flag = 0;
	while (expand)
	{
		if (expand->should_split)
		{
			flag = 1;
			break ;
		}
		if (ft_strlen(expand->content)
			&& expand->content[ft_strlen(expand->content) - 1] == '=')
			break ;
		prev = expand;
		expand = expand->next;
	}
	return (flag);
}

void	assignment_split_check(char **argument, t_expand *expand)
{
	t_expand	*tmp;
	t_expand	*prev;
	int			flag;

	if (ft_strcmp(argument[0], "export"))
		return ;
	tmp = expand;
	prev = NULL;
	flag = find_split_flag(tmp, prev);
	update_split_flag(tmp, prev, flag);
}

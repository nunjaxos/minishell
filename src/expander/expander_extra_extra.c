/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_extra_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:03:38 by amouhand          #+#    #+#             */
/*   Updated: 2024/09/01 08:04:33 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

void	add_to_expand(void)
{
	t_expand	*expand;
	t_expand	*tmp;

	expand = get_parser()->expand;
	tmp = expand;
	while (tmp)
		tmp = tmp->next;
	tmp = ft_malloc(sizeof(t_expand));
	if (!tmp)
		return ;
	tmp->content = NULL;
	tmp->should_split = false;
	tmp->in_single_quotes = false;
	tmp->in_double_quotes = false;
	tmp->next = NULL;
	if (expand)
	{
		while (expand->next)
			expand = expand->next;
		expand->next = tmp;
	}
	else
		get_parser()->expand = tmp;
}

int	calculate_result_size(t_expand *expand)
{
	char	**tmp;
	int		count;

	count = 1;
	while (expand)
	{
		if (expand->should_split)
		{
			tmp = further_split(expand->content, " \t\n\r\f\v");
			count += count_char_array(tmp) - 1;
			free_char_array(tmp);
		}
		expand = expand->next;
	}
	return (count);
}

void	fill_result_array(char **result, t_expand *expand)
{
	char	**tmp;
	int		count;
	int		i;

	count = 0;
	while (expand)
	{
		if (!expand->should_split)
			result[count] = ft_strjoin_free(result[count], expand->content, 1);
		else
		{
			tmp = further_split(expand->content, " \t\n\r\f\v");
			i = 0;
			while (tmp[i])
			{
				result[count] = ft_strjoin_free(result[count], tmp[i], 1);
				i++;
				if (tmp[i])
					count++;
			}
			free_char_array(tmp);
		}
		expand = expand->next;
	}
	result[++count] = NULL;
}

char	**joining_expand_list(t_cmd *cmd)
{
	t_expand	*expand;
	char		**result;
	int			count;

	assignment_split_check(cmd->args, get_parser()->expand);
	expand = get_parser()->expand;
	count = calculate_result_size(expand);
	result = ft_calloc(sizeof(char *), (count + 1));
	if (!result)
		return (NULL);
	expand = get_parser()->expand;
	fill_result_array(result, expand);
	return (free_expand_list(), result);
}

void	update_split_flag(t_expand *expand, t_expand *prev, int flag)
{
	while (expand)
	{
		if (!flag && (prev && ft_strlen(prev->content)
				&& prev->content[ft_strlen(prev->content) - 1] == '='))
		{
			expand->should_split = false;
			break ;
		}
		prev = expand;
		expand = expand->next;
	}
}

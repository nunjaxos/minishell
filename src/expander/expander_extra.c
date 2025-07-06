/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 11:23:34 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/30 18:05:24 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

void	expand_list_process(char *arg, int flag, int expand)
{
	add_to_expand();
	add_content_to_expand(arg);
	if (flag == 0 && expand)
		add_should_split_to_expand(space_available(arg));
	else
		add_should_split_to_expand(false);
	add_in_single_quotes_to_expand(flag == 1);
	add_in_double_quotes_to_expand(flag == 2);
}

void	add_in_double_quotes_to_expand(bool in_double_quotes)
{
	t_expand	*expand;

	expand = get_parser()->expand;
	while (expand->next)
		expand = expand->next;
	expand->in_double_quotes = in_double_quotes;
}

void	add_in_single_quotes_to_expand(bool in_single_quotes)
{
	t_expand	*expand;

	expand = get_parser()->expand;
	while (expand->next)
		expand = expand->next;
	expand->in_single_quotes = in_single_quotes;
}

void	add_should_split_to_expand(bool should_split)
{
	t_expand	*expand;

	expand = get_parser()->expand;
	while (expand->next)
		expand = expand->next;
	expand->should_split = should_split;
}

void	add_content_to_expand(char *content)
{
	t_expand	*expand;

	expand = get_parser()->expand;
	while (expand->next)
		expand = expand->next;
	expand->content = ft_strdup(content);
}

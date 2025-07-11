/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnemili <abnemili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:35:36 by abnemili          #+#    #+#             */
/*   Updated: 2025/07/03 14:44:13 by abnemili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_env	*g_envp;

int	process_regular_char(char *content, int *i, t_expand_data *data)
{
	if (!(*(data->res) = realloc_result(*(data->res), data->max, *(data->len)
				+ 2)))
		return (0);
	(*(data->res))[(*(data->len))++] = content[(*i)++];
	return (1);
}

int	process_expansion_loop(char *content, t_expand_data *data)
{
	int	i = 0;

	while (content[i])
	{
		if (content[i] == '$')
		{
			i++;
			if (!process_dollar_expansion(content, &i, data))
				return (0);
		}
		else if (!process_regular_char(content, &i, data))
			return (0);
	}
	return (1);
}

char	*expand_token_content(char *content, int exit_code, int should_expand)
{
	char			*res;
	int				len = 0;
	int				max = 1024;
	t_expand_data	data;

	if (!content || !should_expand)
		return (ft_strdup(content));
	if (!(res = malloc(max)))
		return (NULL);
	data = (t_expand_data){&res, &len, &max, exit_code};
	if (!process_expansion_loop(content, &data))
		return (free(res), NULL);
	res[len] = '\0';
	return (res);
}

void	handle_word_token(t_elem *curr, int exit_code)
{
	char	*exp;

	exp = expand_token_content(curr->content, exit_code, 1);
	if (exp)
	{
		free(curr->content);
		curr->content = exp;
		curr->type = WORD;
	}
}

void	expand_tokens(t_elem *token, int exit_code)
{
	t_elem	*curr;

	curr = token;
	while (curr)
	{
		if (curr->type == QUOTE || curr->type == DQUOTE)
			handle_quoted_token(curr, exit_code);
		else if ((curr->type == WORD || curr->type == ENV)
			&& curr->state != IN_QUOTE)
			handle_word_token(curr, exit_code);
		curr = curr->next;
	}
}






/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:10:13 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/25 17:23:35 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*tokenizer(char **commands, int *expand_check)
{
	t_token	*head;
	t_token	*tmp;
	int		i;

	i = 0;
	if (token_init(&head, commands))
		return (NULL);
	tmp = head;
	while (head)
	{
		head->value = ft_malloc(sizeof(char) * (ft_strlen(commands[i]) + 1));
		if (!head->value)
			return (NULL);
		ft_strcpy(head->value, commands[i]);
		give_type(head, expand_check[i]);
		head = head->next;
		i++;
	}
	head = tmp;
	return (head);
}

void	give_type(t_token *token, int expand_check)
{
	if (expand_check)
		token->type = WORD;
	else if (!ft_strcmp(token->value, "|"))
		token->type = PIPE;
	else if (!ft_strcmp(token->value, ">"))
		token->type = REDIR;
	else if (!ft_strcmp(token->value, "<"))
		token->type = INPUT;
	else if (!ft_strcmp(token->value, ">>"))
		token->type = APPEND;
	else if (!ft_strcmp(token->value, "<<"))
		token->type = HEREDOC;
	else
		token->type = WORD;
}

int	token_init(t_token **head, char **commands)
{
	t_token	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (commands[i])
		i++;
	*head = ft_malloc(sizeof(t_token));
	if (!*head)
		return (1);
	tmp = *head;
	while (j < i - 1)
	{
		tmp->next = ft_malloc(sizeof(t_token));
		if (!tmp->next)
			return (1);
		tmp = tmp->next;
		j++;
	}
	tmp->next = NULL;
	return (0);
}

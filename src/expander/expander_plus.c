/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_plus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 19:40:58 by amouhand          #+#    #+#             */
/*   Updated: 2024/09/01 09:09:33 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	*get_value(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->key && !ft_strcmp(tmp->key, key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_after(char *arg)
{
	char	*after;
	int		j;
	int		i;

	j = 0;
	while (arg[j] && arg[j] != '$')
		j++;
	j++;
	while (arg[j] && arg[j] != '$' && arg[j] != '\"' && arg[j] != '\''
		&& arg[j] != ' ' && arg[j] != '\t' && arg[j] != '=' && arg[j] != '+')
		j++;
	i = j;
	while (arg[i])
		i++;
	after = ft_malloc(sizeof(char) * (i - j + 1));
	if (!after)
		return (NULL);
	i = 0;
	while (arg[j])
		after[i++] = arg[j++];
	after[i] = '\0';
	return (after);
}

char	*get_expand(char *expand, int flag)
{
	char	*key;
	char	*value;

	key = extract_key(expand);
	if (!key)
		return (NULL);
	value = handle_key_conditions(key, flag, expand);
	ft_free(key);
	return (value);
}

char	*extract_key(char *expand)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	j = 0;
	while (expand[i] && expand[i] != '$' && expand[i] != '\"'
		&& expand[i] != '\'' && expand[i] != ' '
		&& expand[i] != '\t' && expand[i] != '='
		&& expand[i] != '+')
		i++;
	key = ft_malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	while (j < i)
	{
		key[j] = expand[j];
		j++;
	}
	key[i] = '\0';
	return (key);
}

char	*handle_key_conditions(char *key, int flag, char *expand)
{
	char	*value;

	value = NULL;
	if ((key[0] == '\0' || (flag == 2 && key[0] == '\"')) && (flag != 0
			|| (expand[0] != '\"' && expand[0] != '\'')))
		return (ft_strdup("$"));
	if (flag == 1)
	{
		value = ft_strjoin("$", key);
		return (value);
	}
	if (key[0] == '?')
		return (ft_strjoin_free(ft_itoa(get_parser()->exit_status),
				ft_substr(key, 1, strlen(key) - 1), 2));
	value = ft_strdup(get_value(key, get_parser()->env));
	if (!value)
		return (ft_strdup(""));
	return (value);
}

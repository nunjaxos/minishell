/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_plusplus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 20:00:39 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/30 18:05:57 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	*get_before(char *arg)
{
	int		i;
	int		j;
	int		check;
	int		tmp;
	char	*before;

	i = 0;
	j = 0;
	check = 0;
	tmp = 0;
	while (arg[i] && arg[i] != '$')
		i++;
	before = ft_malloc(sizeof(char) * (i + 1));
	if (!before)
		return (NULL);
	i = 0;
	while (arg[i] && arg[i] != '$')
	{
		process_characters(arg, &i, &check, &tmp);
		before[j++] = arg[i++];
	}
	before[j] = '\0';
	return (before);
}

void	process_characters(char *arg, int *i, int *check, int *tmp)
{
	if (!(*check) && (arg[*i] == '\'' || arg[*i] == '\"'))
	{
		if (arg[*i] == '\'')
			*check = 1;
		else
			*check = 2;
		*tmp = arg[*i];
	}
	else if (*check && arg[*i] == *tmp)
		*check = 0;
}

char	*remove_quotes(char *arg, int *flag)
{
	int		new_length;
	char	*result;

	new_length = count_chars_without_quotes(arg, flag);
	result = ft_malloc(sizeof(char) * new_length);
	if (!result)
		return (NULL);
	copy_chars_without_quotes(result, arg, flag);
	ft_free(arg);
	arg = NULL;
	return (result);
}

int	count_chars_without_quotes(char *arg, int *flag)
{
	int	i;
	int	j;
	int	tmp;
	int	check;

	init_vars(&i, &j, &tmp);
	check = *flag;
	while (arg[i])
	{
		if ((arg[i] == '\"' || arg[i] == '\'') && !check)
		{
			set_check(arg, &i, &check);
			tmp = arg[i++];
		}
		else if (check && arg[i] == tmp)
		{
			check = 0;
			i++;
		}
		else
			increment_vars(&i, &j, NULL, NULL);
	}
	return (j + 1);
}

void	copy_chars_without_quotes(char *result, char *arg, int *flag)
{
	int	i;
	int	j;
	int	tmp;

	init_vars(&i, &j, &tmp);
	while (arg[i])
	{
		if ((arg[i] == '\"' || arg[i] == '\'') && !*flag)
		{
			set_check(arg, &i, flag);
			tmp = arg[i++];
		}
		else if (*flag && (arg[i] == '\"' || arg[i] == '\''))
		{
			if ((*flag == 1 && arg[i] == '\'') || (*flag == 2
					&& arg[i] == '\"'))
				set_and_increment(&i, flag);
			else
				result[j++] = arg[i++];
		}
		else
			result[j++] = arg[i++];
	}
	result[j] = '\0';
}

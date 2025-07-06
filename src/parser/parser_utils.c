/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:45:41 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/25 17:23:26 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	**mini_parsing(char *command, int **expand_check)
{
	char	**result;
	int		*array;
	int		k;
	int		i;
	int		j;

	k = -1;
	i = 0;
	if (setting_parser(command, &result, expand_check))
		return (NULL);
	array = *expand_check;
	while (command[i])
	{
		i = skip_segment(command, i, &j);
		if (i != j)
		{
			k++;
			result[k] = copy_segment(command, j, i, &array[k]);
		}
	}
	result[++k] = NULL;
	return (result);
}

int	skip_segment(char *command, int i, int *j)
{
	i = skip_whitespace(command, i);
	(*j) = i;
	if (command[i] == '\"' || command[i] == '\'')
		i = skip_quotes(command, i);
	else if (command[i] && (command[i] == '|' || command[i] == '<'
			|| command[i] == '>'))
		i = skip_special_char(command, i);
	else
		i = skip_everything_else(command, i);
	return (i);
}

int	count_parse(char *command)
{
	int	i;
	int	l;
	int	tmp;

	i = 0;
	l = 0;
	tmp = 0;
	if (!command)
		return (0);
	while (command[i])
	{
		i = skip_whitespace(command, i);
		if ((command[i] == '\"' || command[i] == '\''))
			i = handle_quotes(command, i, &l, &tmp);
		else if (command[i] && (command[i] == '|' || command[i] == '<'
				|| command[i] == '>'))
			i = handle_special_characters(command, i, &l);
		else if (command[i])
			i = handle_regular_characters(command, i, &l, &tmp);
	}
	return (l);
}

int	count_char_array(char **commands)
{
	int	i;

	if (!commands)
		return (0);
	i = 0;
	while (commands[i])
		i++;
	return (i);
}

int	setting_parser(char *command, char ***result, int **expand_check)
{
	int	count;
	int	i;

	i = -1;
	if (!command)
		return (1);
	count = count_parse(command);
	if (!count)
		return (1);
	*result = ft_malloc(sizeof(char *) * (count + 1));
	if (!(*result))
		return (1);
	while (++i < count)
		(*result)[i] = NULL;
	*expand_check = ft_calloc((sizeof(int)), count);
	if (!(*expand_check))
		return (ft_free(*result), 1);
	return (0);
}

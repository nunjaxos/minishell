/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:54:04 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/30 19:17:14 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	*get_path(char *command, char **path)
{
	int		i;
	char	*tmp;
	char	*to_free;

	if (!command || !path)
		return (NULL);
	i = 0;
	if (!ft_strcmp(command, "cd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "exit")
		|| !ft_strcmp(command, "echo") || !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "env"))
		return (command);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		to_free = tmp;
		tmp = ft_strjoin(tmp, command);
		ft_free(to_free);
		if (!access(tmp, F_OK))
			return (ft_free(command), tmp);
		ft_free(tmp);
		i++;
	}
	return (NULL);
}

int	isspecial(char *command, int i)
{
	int	tmp;
	int	check;

	check = 0;
	if (is_initial_special(command, i))
	{
		tmp = command[i++];
		handle_special_cases(command, i, tmp, &check);
		if (!check)
			return (1);
	}
	return (0);
}

int	is_initial_special(char *command, int i)
{
	return ((!i || command[i - 1] == '\t' || command[i - 1] == ' ')
		&& (command[i] == '\'' || command[i] == '\"'));
}

int	handle_special_cases(char *command, int i, int tmp, int *check)
{
	if (command[i] == '|' || command[i] == '<' || command[i] == '>')
		i++;
	else
		*check = 1;
	if (command[i] == command[i - 1] && command[i] != '|')
		i++;
	if (command[i] == tmp)
		i++;
	else
		*check = 1;
	if (command[i] != ' ' && command[i] != '\t' && command[i] != 0
		&& command[i] != '|' && command[i] != '<' && command[i] != '>')
		*check = 1;
	return (i);
}

int	check_for_quotes(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\"' || command[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

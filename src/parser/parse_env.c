/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:39:25 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/30 18:27:47 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	set_path(t_cmd **cmd, t_env *env)
{
	int		i;
	char	*path;
	char	**paths;

	path = get_value("PATH", env);
	paths = NULL;
	i = 0;
	if (path)
		paths = ft_split(path, ':');
	while (cmd[i])
	{
		path_check(cmd[i], paths);
		i++;
	}
	if (paths)
		free_char_array(paths);
	return (0);
}

char	*set_cwd(void)
{
	char	*cwd;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	add_alloc(cwd);
	if (!cwd)
		cwd = ft_strdup(get_value("PWD", get_parser()->env));
	prompt = ft_strjoin_free("minishell$", cwd, 0);
	if (!prompt)
		ft_putstr_fd("Error: Can't Allocate Memory\n", 2);
	prompt = ft_strjoin_free(prompt, ": ", 1);
	if (!prompt)
		ft_putstr_fd("Error: Can't Allocate Memory\n", 2);
	return (prompt);
}

int	if_builtin(char *arg)
{
	if (!ft_strcmp(arg, "echo") || !ft_strcmp(arg, "cd") || !ft_strcmp(arg,
			"pwd") || !ft_strcmp(arg, "export") || !ft_strcmp(arg, "unset")
		|| !ft_strcmp(arg, "env") || !ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}

int	test_path(char **path, t_cmd *cmd)
{
	char	*temp;

	if (!path)
		return (cmd->access = NOT_AVAIL, 0);
	if (ft_strchr(cmd->args[0], '/'))
		return (0);
	temp = get_path(cmd->args[0], path);
	if (!temp)
		return (cmd->access = CMD_NOT_FOUND, 1);
	cmd->args[0] = temp;
	if (access(cmd->args[0], F_OK) == -1)
		cmd->access = CMD_NOT_FOUND;
	else if (!access(cmd->args[0], F_OK))
	{
		if (access(cmd->args[0], X_OK) == -1)
			cmd->access = NOT_EXEC;
		else
			cmd->access = IS_EXEC;
	}
	if (cmd->access == IS_EXEC)
		return (1);
	return (0);
}

void	test_binaries(t_cmd *cmd)
{
	struct stat	sb;

	if (!ft_strchr(cmd->args[0], '/'))
	{
		cmd->access = CMD_NOT_FOUND;
		return ;
	}
	if (cmd->args[0] && !access(cmd->args[0], F_OK))
	{
		if (!stat(cmd->args[0], &sb) && S_ISDIR(sb.st_mode))
			cmd->access = IS_A_DIR;
		else
		{
			if (access(cmd->args[0], X_OK) == -1)
				cmd->access = NOT_EXEC;
			else
				cmd->access = IS_EXEC;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 11:17:29 by abhmidat          #+#    #+#             */
/*   Updated: 2025/06/15 11:37:42 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *g_envp = NULL;

char *get_home_path(void)
{
    t_env *home = find_env(g_envp, "HOME");
    if (home && home->content)
        return home->content;
    return NULL;
}

int	norm_path(char *path)
{
	if (!path)
	{
		fprintf(stderr, "minishell: cd: HOME not set\n");
        return (1);
    }
	return (0);
}

int	norm_chdir(char *path)
{
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}

int	norm_getcwd(char *buf, size_t size)
{
	if (!getcwd(buf, size))
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	return (0);
}

int builtin_cd(char **args)
{
    char cwd[PATH_MAX];
    char old_pwd[PATH_MAX];
    char *path;

    if (!getcwd(old_pwd, sizeof(old_pwd)))
        old_pwd[0] = '\0';
    if (!args[1])
    {
        path = get_home_path();
        if (norm_path(path))
		return (1);
    }
    else
        path = args[1];
	if (norm_chdir(path) || norm_getcwd(cwd, sizeof(cwd)))
		return (1);
    update_env(&g_envp, "PWD", cwd);
    update_env(&g_envp, "OLDPWD", old_pwd);
    return 0;
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)envp;

    char *args1[] = {"cd", "/tmp", NULL};
    int ret = builtin_cd(args1);
    printf("Return value: %d\n", ret);

    return 0;
}

#include "../../include/executor.h"

void	close_fds(int cmd_count, int *fd)
{
	int	i;

	i = 0;
	while (i < 2 * (cmd_count - 1))
	{
		close(fd[i]);
		i++;
	}
}

void execute_cmd(t_cmd *cmd, int cmd_count, int *fd, int i, t_data *data)
{
	if (cmd->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(cmd, fd, i, cmd_count);

		if (cmd->in_file == -1 || cmd->out_file == -1)
			exit_status("Redirection error", 1);
		error_display(cmd);
		if (check_builtins(data, cmd, cmd->pid))
			exit(0);
		execve(cmd->full_cmd[0], cmd->full_cmd, convert_path_to_array(data->n_env, data));
		perror("execve");
		free_data(data);
		exit(255);
	}
}


void child_process(t_cmd *cmd, int *fd, int i, int cmd_count)
{
	if (!i)
		dup2(cmd->in_file, STDIN_FILENO);
	if (i == cmd_count - 1)
		dup2(cmd->out_file, STDOUT_FILENO);

	if (i != 0)
	{
		if (cmd->in_file == STDIN_FILENO)
			cmd->in_file = fd[(i - 1) * 2];
		dup2(cmd->in_file, STDIN_FILENO);
	}
	if (i != cmd_count - 1)
	{
		if (cmd->out_file == STDOUT_FILENO)
			cmd->out_file = fd[i * 2 + 1];
		dup2(cmd->out_file, STDOUT_FILENO);
	}
}

void forking_accordingly(t_cmd *cmd, int cmd_count, int *fd, t_data *data)
{
	int		i = 0;
	int		*last;

	g_sigchild = 1;
	while (i < cmd_count && cmd)
	{
		last = get_lastpid();
		signal(SIGQUIT, sigquit_handler);
		cmd->pid = fork();
		if (cmd->pid < 0)
			exit_status("fork failed", 1);
		if (!cmd->next && cmd->pid)
			*last = cmd->pid;
		execute_cmd(cmd, cmd_count, fd, i, data);
		cmd = cmd->next;
		i++;
	}
}

void create_pipe(t_cmd *cmds, int cmd_count, t_data *data)
{
	int		*fd;
	int		status = 0;
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = cmds;
	fd = ft_malloc(sizeof(int) * (2 * (cmd_count - 1)), &(data->alloc));
	while (i < cmd_count - 1)
	{
		if (pipe(fd + i * 2) < 0)
			exit_status("pipe failed", 1);
		i++;
	}
	forking_accordingly(cmds, cmd_count, fd, data);
	close_fds(cmd_count, fd);
	cmd = cmds;
	while (cmd)
	{
		pipe_utils(cmd, status, data);
		cmd = cmd->next;
	}
	ft_free(fd, &(data->alloc));
	g_sigchild = 0;
	signal(SIGQUIT, sigquit_handler);
}

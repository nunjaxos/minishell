#include "../../include/executor.h"

void	exit_status(char *failed, int status)
{
	ft_printf("%s: %s\n", failed, strerror(status));
	free_parser(get_parser());
	exit(1);
}

void	one_cmd_norm(t_cmd *cmd, t_data *data, pid_t pid)
{
	if (pid == -1)
		exit_status("fork", -1);
	if (pid == 0)
	{
		if (cmd->in_file != 0)
			dup2(cmd->in_file, 0);
		if (cmd->out_file != 1)
			dup2(cmd->out_file, 1);
		error_display(cmd);
		if (check_builtins(data, cmd, pid))
		{
			free_parser(data);
			exit(0);
		}
		execve(cmd->full_cmd[0], cmd->full_cmd, convert_path_to_array(data->n_env, data));
		perror("execve");
		exit(255);
	}
}

void exec_one_command(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	g_sigchild = 1;
	pid = fork();
	signal(SIGQUIT, sigquit_handler);
	if (pid == -1)
		exit_status("fork", -1);
	if (pid == 0)
	{
		if (cmd->in_file != STDIN_FILENO)
			dup2(cmd->in_file, STDIN_FILENO);
		if (cmd->out_file != STDOUT_FILENO)
			dup2(cmd->out_file, STDOUT_FILENO);
		if (check_builtins(data, cmd, pid))
			exit(0);
		execve(cmd->full_cmd[0], cmd->full_cmd, convert_path_to_array(data->n_env, data));
		perror("execve");
		free_data(data);
		exit(255);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		data->error = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		data->error = WTERMSIG(status) + 128;
	g_sigchild = 0;
	signal(SIGQUIT, sigquit_handler);
}

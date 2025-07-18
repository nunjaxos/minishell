#include "../../include/executor.h"

void	exit_status(char *failed, int code, t_data *data)
{
	ft_printf("%s: %s\n", failed, strerror(code));
	free_data(data);
	exit(1);
}

void exec_one_command(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	int		status;

	g_sigchild = 1;
	cmd->pid = 1;
	if (before_child(cmd, data))
		return ;
	pid = fork();
	signal(SIGQUIT, sigquit_handler);
	if (pid == -1)
		exit_status("fork", -1, data);
	if (pid == 0)
	{
		if (cmd->in_file != STDIN_FILENO)
			dup2(cmd->in_file, STDIN_FILENO);
		if (cmd->out_file != STDOUT_FILENO)
			dup2(cmd->out_file, STDOUT_FILENO);
        error_display(cmd);
		if (check_builtins(data, cmd, pid))
			exit(0);
		char *full_path = find_full_path(cmd->full_cmd[0], data->n_env);
    	if (full_path)
    	{
        	free(cmd->full_cmd[0]);
        	cmd->full_cmd[0] = full_path;
    	}
    	else
    	{
        	// Command not found error handling
        	ft_putstr_fd(cmd->full_cmd[0], 2);
        	ft_putstr_fd(": command not found\n", 2);
        	free_data(data);
        	exit(127);
    	}
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
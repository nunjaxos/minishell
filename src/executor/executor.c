#include "../../include/executor.h"

int	execute_commands(t_data *data)
{
	t_cmd	*cmd = data->head;
	int		cmd_count = count_commands(cmd);

	update_last_cmd(data); // Set `_` env var with last command

	if (cmd_count == 1)
		exec_one_command(cmd, data);
	else
		create_pipe(cmd, cmd_count, data);

	return (0);
}

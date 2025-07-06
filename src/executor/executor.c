
#include "../../include/executor.h"

int	execute_commands(t_parser *parser)
{
	t_cmd *cmd = parser->head; // get linked list

	if (count_commands(cmd) == 1)
	{
		update_last_cmd(get_parser());
		exec_one_command(cmd, parser);
	}
	else
	{
		update_last_cmd(get_parser());
		create_pipe(cmd, count_commands(cmd));
	}
	return (0);
}

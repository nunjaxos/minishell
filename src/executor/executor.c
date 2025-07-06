/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouaoud <ybouaoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:18:48 by amouhand          #+#    #+#             */
/*   Updated: 2024/08/28 22:34:17 by ybouaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

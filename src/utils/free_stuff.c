#include "../../include/executor.h"

void	free_tokens(t_token **head, t_data *data)
{
	t_token	*tmp;
	t_token	*current;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->value)
		{
			ft_free(tmp->value, &(data->alloc));
			tmp->value = NULL;
		}
		ft_free(tmp, &(data->alloc));
		tmp = NULL;
	}
	*head = NULL;
}

void	free_char_array(char **array, t_data *data)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		if (array[i])
		{
			ft_free(array[i], &(data->alloc));
			array[i] = NULL;
		}
		i++;
	}
	ft_free(array, &(data->alloc));
	array = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->full_cmd)
		free_char_array(cmd->full_cmd);
	if (cmd->redirections)
		free_redirections(cmd->redirections);
	ft_free(cmd);
	cmd = NULL;
}

void	free_redirections(t_redirection *redirections)
{
	t_redirection	*tmp;

	while (redirections)
	{
		tmp = redirections;
		redirections = redirections->next;
		ft_free(tmp->arg);
		ft_free(tmp);
		tmp = NULL;
	}
	redirections = NULL;
}

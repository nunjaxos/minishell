#include "../../include/executor.h"

void	ft_pwd(pid_t pid, t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	add_alloc(pwd, &(data->alloc));
	ft_putendl_fd(pwd, 1);
	ft_free(pwd, &(data->alloc));
	check_for_child(pid, 0, data);
}

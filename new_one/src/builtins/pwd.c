#include "../../include/executor.h"

void	ft_pwd(pid_t pid, t_data *data)
{
	(void)pid;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	add_alloc(pwd, &(data->alloc));
	ft_putendl_fd(pwd, 1);
	check_for_child(pid, 0, data);
}

// int	main(void)
// {
// 	t_data	data;

// 	// Initialize the t_data structure
// 	ft_bzero(&data, sizeof(t_data));
// 	data.alloc = NULL; // In case your allocator uses this

// 	// Simulate running `pwd` as a built-in (pid = 0)
// 	ft_pwd(0, &data);

// 	return 0;
// }
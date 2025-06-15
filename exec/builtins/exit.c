#include "minishell.h"

int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_error(const char *msg)
{
	while (*msg)
		write(2, msg++, 1);
}

int	minishell_exit(int argc, char **argv)
{
	int	exit_status;

	exit_status = 0;
	if (argc == 1)
		exit(0);
	else if (argc == 2)
	{
		if (!is_number(argv[1]))
		{
			print_error("exit: numeric argument required\n");
			exit(255);
		}
		exit_status = atoi(argv[1]);
		exit(exit_status);
	}
	else
	{
		print_error("exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int main(int ac, char **av)
{
	minishell_exit(ac, av);
}

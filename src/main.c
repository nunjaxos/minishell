#include "../include/executor.h"

int	g_sigchild;

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		last_exit_code = 0;

	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);

	init_env_list(env); // initializes environment into your global/env storage

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (process_input(input, &last_exit_code))
			add_history(input);
		free(input);
	}
	return (0);
}

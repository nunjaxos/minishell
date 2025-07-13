#include "../../include/executor.h"

void	init_vars(int *i, int *j, int *tmp)
{
	*i = 0;
	*j = 0;
	*tmp = 0;
}

void	increment_vars(int *i, int *j, int *k, int *l)
{
	if (i)
		(*i)++;
	if (j)
		(*j)++;
	if (k)
		(*k)++;
	if (l)
		(*l)++;
}

void	set_check(char *arg, int *i, int *flag)
{
	if (arg[(*i)] == '\'')
		(*flag) = 1;
	else
		(*flag) = 2;
}

void	set_and_increment(int *i, int *flag)
{
	*flag = 0;
	(*i)++;
}

void	heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

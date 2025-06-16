#include "minishell.h"

int is_n_flag(const char *str)
{
	int	i;

    if (str[0] != '-')
        return 0;
	i = 1;
    while (str[i])
    {
        if (str[i] != 'n')
            return 0;
		i++;
    }
    return 1;
}

void echo(int argc, char **argv) 
{
    int i = 1;
    int new_line = 1;

    while (i < argc && is_n_flag(argv[i]))
    {
        new_line = 0;
        i++;
    }

    while (i < argc)
    {
        printf("%s", argv[i]);
        if (i < argc - 1)
            printf(" ");
        i++;
    }

    if (new_line)
        printf("\n");
}

int main(int ac, char **av)
{
    echo(ac, av);
    return 0;
}


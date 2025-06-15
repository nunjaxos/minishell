#include "minishell.h"

void echo(int argc, char **argv) 
{
    int i;
    int new_line;

    i = 1;
    new_line = 1;
    while (i < argc && ft_strcmp(argv[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (i < argc; i++)
    {
        printf("%s", argv[i]);
        if (i < argc - 1)
            printf(" ");
    }
    if (newline)
        printf("\n");
}

int main(int ac, char **av)
{
	echo(ac, av);
	return (0);
}

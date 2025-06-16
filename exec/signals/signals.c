#include "minishell.h"

void handle_eof(char *line)
{
    if (line == NULL)
    {
        write(STDOUT_FILENO, "exit\n", 5);
        exit(0);
    }
}

void sigint_handler(int signum)
{
    (void)signum;
    rl_replace_line("", 0);
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

void setup_signal_handlers(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}

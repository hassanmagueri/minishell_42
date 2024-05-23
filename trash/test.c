#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t exit_state = 0;

void handle_sigint(int signal)
{
    if (signal == SIGINT)
    {
        exit_state = 1;
        write(1, "\n", 1);
        // rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

int main()
{
    // Install the signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    char *input;
    while (!exit_state)
    {
        input = readline("prompt> ");
        if (input == NULL) break;  // EOF (Ctrl+D)

        // Process the input...

        free(input);
    }

    printf("Exiting...\n");
    return 0;
}

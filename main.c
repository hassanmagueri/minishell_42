#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main() {
    char *cmd;
    
    while (1)
    {
        cmd = readline(ANSI_COLOR_CYAN "→ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "➤ " ANSI_COLOR_RESET);

        free(cmd);
    }
    return 0;
}
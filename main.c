#include "minishell.h"

int main() {
	char *cmd;

	while (1)
	{
		t_token *t = NULL;
		cmd = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		ft_tokenize(&t, cmd);
		
		print_tokens(t);
		free(cmd);
		// if (ft_strncmp(cmd, "ls ", 3) == 0)
		//     execve("/") 
	}
	return 0;
}
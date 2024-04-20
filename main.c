#include "minishell.h"

int main(int argc, char *argv[], char **env) {
	char *input;
	t_lst_env *lst_env;

	lst_env = NULL;
	if (argc > 1)
	{
		printf("%s", argv[0]);
		return (1);
	}
	init_env(&lst_env, env);
	// print_lst_env(lst_env);
	
	while (1)
	{
		t__lst_token *t = NULL;
		t_cmd *cmd = NULL;
		input = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		add_history(input);
		// input = readline("minishell -> ");
		// ft__lst_tokenize(&t, input)
		if (ft__lst_tokenize(&t, input) || generate_errors(&t) == 1)
			continue;
		ft_expand(&t, &lst_env);
		ft_join(&t);
		print__lst_tokens(t);
		ft_cmd(&cmd, &t);
		free(input);
	}
	return 0;
}
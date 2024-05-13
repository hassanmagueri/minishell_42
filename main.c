/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:47:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/13 16:10:42 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int main(int argc, char *argv[], char **env)
{
	char *input;
	// int	e_status;
	t_lst_env *lst_env;
	t_lst_env *last_lst;
	t_data pip;
	lst_env = NULL;
	pip.env = env;
	if (argc > 1)
	{
		printf("%s", argv[0]);
		return (1);
	}
	init_env(&lst_env, env);
	// init_path_env(&pip,lst_env);
	init_path_env(&pip,lst_env,env);
	signal(SIGINT, handle_c_slash_ctrol);
    signal(SIGQUIT, handle_c_slash_ctrol);
	rl_catch_signals = 0;
	while (1)
	{
		t__lst_token *t = NULL;
		t_cmd *cmd = NULL;
		input = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		// input = readline("minishell 😎> ");
		if (input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (input[0]=='\0')
			continue;
		add_history(input);
		if (ft__lst_tokenize(&t, input) || generate_errors(&t) == 1)
			continue;
		print__lst_tokens(t);
		ft_expand(&t, &lst_env);
		ft_join(&t);
		ft_heredoc(&t);
		ft_cmd(&cmd, &t);
		print_lst_cmd(cmd);
		ft_chech_excut_cmd(cmd,lst_env,&pip);
		free(input);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:47:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/24 21:17:18 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
int exit_state ;
int ft_trim(t__lst_token **lst_token)
{
	t__lst_token *cur;

	cur = *lst_token;
	while (cur)
	{
		if (cur->type == DOUB_Q)
			cur->str = ft_strtrim(cur->str, "\"", ALLOC);
		else if (cur->type == SING_Q)
			cur->str = ft_strtrim(cur->str, "\'", ALLOC);
		cur = cur->next;
	}
	return 1;
}

int main(int argc, char *argv[], char **env)
{
	char *input;
	t_lst_env *lst_env;
	t_lst_env *last_lst;
	t_data pip;

	exit_state = 0;
	lst_env = NULL;
	if (argc > 1)
	{
		printf("%s", argv[0]);
		return (1);
	}
	
	init_env(&lst_env, env);
	init_path_env(&pip,&lst_env);
	rl_catch_signals = 0;
	while (1 && isatty(STDIN_FILENO))
	{
		t__lst_token *t = NULL;
		t_cmd *cmd = NULL;
		signal(SIGINT, handle_c_slash_ctrol);
    	signal(SIGQUIT, handle_c_slash_ctrol);
		input = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		// input = readline("~ minishell 😎 ↪ ");
		if (input == NULL)
		{
			printf("exit\n");	
			exit(0);
		}
		if (input[0]=='\0')
			continue;
		add_history(input);
		ft__lst_tokenize(&t, input);
		int n = generate_errors(&t);
		ft_trim(&t);
		if (n)
		{
			exit_state = 2;
			ft_heredoc(&t, &lst_env);
			gc_alloc(0, FREE);
			continue;
		}
		// print__lst_tokens(t);
		ft_expand(&t, &lst_env, exit_state);
		if (ft_join(&t))
			continue;
		ft_heredoc(&t, &lst_env);
		ft_cmd(&cmd, &t);
		// print_lst_cmd(&cmd);
		ft_chech_excut_cmd(cmd,&lst_env,&pip);
		exit_state = cmd->exit_status;
		if (exit_state == 1)
			cmd->exit_status = 1;
			// printf("exit status == %d\n",exit_state);
		free(input);
		//gc_alloc(0, FREE);
	}
	gc_alloc(0, FREE_ENV);
	return (0);
}

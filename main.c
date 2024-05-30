/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:47:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/30 01:13:45 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_var;


int main(int argc, char *argv[], char **env)
{
	char *input;
	t_lst_env *lst_env;
	t_data pip;
	int ex_state;
	int n = 0;
	
	g_var = 0;
	lst_env = NULL;
	if (argc > 1)
		return ((void)argv, 1);
	init_env(&lst_env, env);
	init_path_env(&pip, &lst_env);
	rl_catch_signals = 0;
	ex_state = 0;
	// while(1)
	while (1 && isatty(STDIN_FILENO))
	{
		t__lst_token *lst_token = NULL;
		t_cmd *cmd = NULL;
		signal(SIGINT, handle_c_slash_ctrol);
		signal(SIGQUIT, handle_c_slash_ctrol);
		input = readline("~ minishell 😎 ↪ ");
		if (input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		if (input[0] == '\0')
			continue;
		if (g_var == 1)
			ex_state = 1;
		add_history(input);
		ft__lst_tokenize(&lst_token, input);
		n = ft_parsing(&lst_token, &lst_env, &cmd, &ex_state); //
		if (n)
		{
			ex_state = n;
			continue;
		}
		ft_check_cmd(cmd, &lst_env, &pip, &ex_state);
		free(input);
		g_var = 0;
		gc_alloc(0, FREE);
	}
	gc_alloc(0, FREE_ENV);
	return (0);
}

// export a="a b c"
// export f=$a
// echo $f
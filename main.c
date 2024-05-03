/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:47:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/02 23:13:29 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	init_path_env(t_data *pip,char *env[])
{
	char *str;
	while (env && *env && ft_strncmp(*env, "PATH=", 5) != 0)
        env++;
	if (*env == NULL)
		printf("Path not found");
	*env += 5;
	// printf("%s\n",*pip->env);
	pip->env_path = ft_split(*env, ':');
	if (!pip->env_path)
		printf("Invalid argument");
	pip->infile = -1;
	pip->outfile = -1;
}


int main(int argc, char *argv[], char **env)
{
	char *input;
	t_lst_env *lst_env;
	t_data pip;
	lst_env = NULL;
	pip.env = env;
	if (argc > 1)
	{
		printf("%s", argv[0]);
		return (1);
	}
	init_env(&lst_env, env);
	init_path_env(&pip,pip.env);
	// int i = 0;
	// while(pip.env_path[i])
	// 	printf("%s\n",pip.env_path[i++]);

	// print_lst_env(lst_env);
	
	while (1)
	{
		t__lst_token *t = NULL;
		t_cmd *cmd = NULL;
		// input = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		input = readline("minishell -> 😎 ");
		if (input == NULL || input[0] == '\0')
			continue;
		add_history(input);
		if (ft__lst_tokenize(&t, input) || generate_errors(&t) == 1)
			continue;
		ft_expand(&t, &lst_env);
		ft_join(&t);
		print__lst_tokens(t);
		ft_heredoc(&t);
		ft_cmd(&cmd, &t);
		print_lst_cmd(cmd);
		ft_chech_excut_cmd(cmd,lst_env,&pip);
		// sleep(2);  
		free(input);
	}
	return (0);
}


// path = "bui/";
// path += cmd;
// path += .c;
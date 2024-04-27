/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:47:51 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/27 18:10:19 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	**init_path_env(char *env[])
{
	char **str;
	while (env && *env && ft_strncmp(*env, "PATH=", 5) != 0)
        env++;
	if (*env == NULL)
		printf("Path not found");
	*env += 5;
	// printf("hhhhhhhhh\n");
	str = ft_split(*env, ':');
	if (!str)
		printf("Invalid argument");
	return (str);
}


int main(int argc, char *argv[], char **env)
{
	char *input;
	t_lst_env *lst_env;
	char **env_path;
	lst_env = NULL;

	if (argc > 1)
	{
		printf("%s", argv[0]);
		return (1);
	}
	init_env(&lst_env, env);
	env_path = init_path_env(env);

	// print_lst_env(lst_env);
	
	while (1)
	{
		t__lst_token *t = NULL;
		t_cmd *cmd = NULL;
		input = readline(ANSI_COLOR_CYAN "~ " ANSI_COLOR_BLUE "minishell 😎 " ANSI_COLOR_MAGENTA "↪ " ANSI_COLOR_RESET);
		// input = readline("minishell -> ");
		if (input == NULL || input[0] == '\0')
			continue;
		add_history(input);
		// ft__lst_tokenize(&t, input);
		// input = readline("minishell -> ");
		if (ft__lst_tokenize(&t, input) || generate_errors(&t) == 1)
			continue;
		// ft_heredoc(&t);
		ft_expand(&t, &lst_env);
		ft_join(&t);
		// print__lst_tokens(t);
		ft_cmd(&cmd, &t);
		// printf("ggggggg\n");
		ft_lst_cmd(cmd,env_path);
		// sleep(2);
		free(input);
	}
	return (0);
}


// path = "bui/";
// path += cmd;
// path += .c;
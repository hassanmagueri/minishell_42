/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 16:34:38 by ataoufik          #+#    #+#             */
/*   Updated: 2024/05/28 20:47:13 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_ambiguous_redir(char *str)
{
	if (str == NULL)
	{
		ft_putendl_fd("ambiguous redirect ", 2);
		exit (1);
	}
}

void	ft_open_outfile(t_data *pip, char *str, int signal)
{
	if (signal == 3)
	{
		if (pip->outfile != 1)
			close(pip->outfile);
		if (pip->infile >= 0)
			pip->outfile = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	}
	else if (signal == 0)
	{
		if (pip->outfile != 1)
			close(pip->outfile);
		if (pip->infile >= 0)
			pip->outfile = open(str, O_CREAT | O_WRONLY | O_APPEND, 0666);
	}
}

void	ft_open_infile(t_data *pip, char *str, int signal)
{
	if (signal == 2)
	{
		if (pip->infile != 0)
			close(pip->infile);
		pip->infile = open(str, O_RDONLY);
	}
	else if (signal == 1)
	{
		if (pip->infile != 0)
			close(pip->infile);
		pip->infile = ft_atoi(str);
	}
}

void	ft_redirection(t_cmd *cmd, t_data *pip)
{
	t_redir	*cur;
	int		i;

	i = 0;
	cur = cmd->redir;
	while (cur)
	{
		ft_ambiguous_redir(cur->file_name);
		if (cur->redirection_type == OUTPUT)
			ft_open_outfile(pip, cur->file_name, 3);
		else if (cur->redirection_type == APPEND)
			ft_open_outfile(pip, cur->file_name, 0);
		else if (cur->redirection_type == INPUT)
			ft_open_infile(pip, cur->file_name, 2);
		else if (cur->redirection_type == HEARDOC)
			ft_open_infile(pip, cur->file_name, 1);
		i++;
		cur = cur->next;
	}
}

#include "minishell.h"
void	ft_open_outfile(t_pipe *pip, int i)
{
	if (i == 1)
		pip->outfile = open("outfile", O_CREAT | O_WRONLY | O_APPEND, 0666);
	else if (i == 0)
		pip->outfile = open("outfile", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    else
        pip->outfile = 1;

}

void	ft_messg_error(char *str)
{
	perror(str);
	exit(1);
}

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

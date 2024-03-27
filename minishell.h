#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

#define REDIR 1
#define PIPE 2

typedef struct s_cmd
{
    int type;
}   t_cmd;

typedef struct s_pipe
{
    int type;
    t_cmd *left;
    t_cmd *rigth;
}   t_pipe;



#endif
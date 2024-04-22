/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:42:31 by ataoufik          #+#    #+#             */
/*   Updated: 2024/04/22 08:17:09 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ft_free_node(t_lst_env *node)
{
    if (node)
    {
        free(node->key);
        free(node->value);
        free(node);
    }
}

int ft_unset(t_lst_env **lst, t_cmd *args)
{
    t_lst_env   *cur;
    t_lst_env   *prev;
    t_lst_env   *to_free;
    int i;

    i = 1;
    while (args->cmd[i] != NULL)
    {
        cur = *lst;
        prev = NULL;
        while (cur != NULL)
        {
            if (ft_strncmp(cur->key,args->cmd[i],ft_strlen(args->cmd[i])) == 0)
            {
                to_free = cur;
                if (prev)
                    prev->next= cur->next;
                else
                    *lst = cur->next;
                ft_free_node(to_free);
                cur = cur->next;
            }
            else
            {
                prev = cur;
                cur=cur->next;
            }
        }
        i++;
    }
    return (0);
}


// t_lst_env *create_node(const char *key, const char *value)
// {
//     t_lst_env *node = (t_lst_env *)malloc(sizeof(t_lst_env));
//     node->key = strdup(key);
//     node->value = strdup(value);
//     node->next = NULL;
//     return node;
// }

// void print_list(t_lst_env *lst)
// {
//     while (lst)
//     {
//         printf("Key: %s, Value: %s\n", lst->key, lst->value);
//         lst = lst->next;
//     }
// }
// int main(int argc, char **argv)
// {
//     t_lst_env *head = create_node("HOME", "/home/user");
//     head->next = create_node("USER", "username");
//     head->next->next = create_node("PATH", "/usr/bin:/bin");
//     head->next->next->next = create_node("PWD", "/usr/bin:/bin");
//     head->next->next->next->next = create_node("AA", "111111111111111");

//     printf("Before unset:\n");
//     print_list(head);

//     t_cmd args;
//     args.cmd = (char **)malloc(5 * sizeof(char *));
//     args.cmd[0] = strdup("unset");
//     args.cmd[1] = strdup("AA");
//     args.cmd[2] = NULL;
//     args.cmd[3] = NULL;
//     args.cmd[4] = NULL;

//     ft_unset(&head, &args); 

//     printf("\nAfter unset:\n");
//     print_list(head);

//     for (int i = 0; i < 4; i++)
//         free(args.cmd[i]);
//     free(args.cmd);

//     return 0;
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emagueri <emagueri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:41:20 by emagueri          #+#    #+#             */
/*   Updated: 2024/05/15 14:46:50 by emagueri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_spliter(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

int wordlen(char *str)
{
    int i = 0;
    while (!is_spliter(str[i]) && str[i])
        i++;
    return i;
}

int count_words(char *s)
{
    int count = 0;
    int i = 0;
    while (s[i])
    {
        while (is_spliter(s[i]))
            i++;
        if (s[i])
            count++;
        while (!is_spliter(s[i]) && s[i])
            i++;
    }
    return count;
}

char **ft_split_ws(char *str, t_gc_type type)
{
    char **res;
    int i = 0;
    int index = 0;
    
    res = gc_alloc((count_words(str) + 1) * sizeof(char *), type);
    while (str[i] && index < count_words(str))
    {
        while (is_spliter(str[i]))
            i++;
        char *word = gc_alloc(wordlen(str + i) + 1, type);
        int j = 0;
        while (j < wordlen(str + i))
        {
            word[j] = str[i + j];
            j++;
        }
        word[j] = '\0';
        res[index] = word;
        while (!is_spliter(str[i]) && str[i])
            i++;
        index++;
    }
    res[index] = NULL;
    return res;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_msgerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataoufik <ataoufik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:58:40 by ataoufik          #+#    #+#             */
/*   Updated: 2024/03/18 17:02:44 by ataoufik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	free_2d_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_message_error(char *str)
{
	// ft_putendl(str , 2); // use the fanction of libft
	exit(1);
}

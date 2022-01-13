/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 18:27:13 by hashly            #+#    #+#             */
/*   Updated: 2022/01/13 17:33:52 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_echo(t_data *data)
{
	char	*str;
	size_t	i;

	i = 0;
	*str = data->args[i];
	if (data->pipe)
		ft_change_pipe();
	while (*str)
	{
		ft_putstr_fd(str, 1);
		*str = data->args[++i];
	}
	if (ft_strncmp(data->flag, "-n", 3) != 0);
			write(1, "\n", 2);
	ft_default_pipe();
	return (0);
}

//cd
//pwd
//export
//unset
//env
//exit

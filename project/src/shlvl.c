/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:51:12 by hashly            #+#    #+#             */
/*   Updated: 2022/04/23 16:58:46 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	processing_valid_shlvl(char **value)
{
	if (ft_atoi(*value) < 0)
	{
		free(*value);
		*value = ft_strdup("0");
	}
}

void	up_shlvl(char ***env)
{
	char		*shlvl;
	long long	shlvl_int;
	char		**arg;

	arg = NULL;
	shlvl = ft_strdup(ft_getenv("SHLVL", *env));
	if (!shlvl)
		shlvl = ft_strdup("1");
	shlvl_int = ft_atoi(shlvl) + 1;
	if (ft_atoi_long_long(shlvl) == 2 && shlvl_int - 1 != 2)
		shlvl_int = 1;
	free(shlvl);
	if (shlvl_int >= 2000000)
	{
		ft_putstr_fd("minishell: warning: shell level (", STD_ERR);
		ft_putnbr_fd(shlvl_int, STD_ERR);
		ft_putendl_fd(") too high, resetting to 1", STD_ERR);
		shlvl_int = 1;
	}
	shlvl = ft_strjoin_free_s2("SHLVL=", ft_itoa(shlvl_int));
	arg = ft_add_line(arg, shlvl);
	free (shlvl);
	ft_export(arg, &env);
	ft_free_str_of_str(&arg);
}

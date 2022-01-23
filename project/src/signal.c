/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:59:31 by hashly            #+#    #+#             */
/*   Updated: 2022/01/23 15:48:40 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_d(int signo)
{
	signo = 0;
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_free_envp();
	exit(0);
}

static void	sig_int(int signo)
{
	char	*promt;

	signo = 0;
	promt = get_promt();
	write(1, "\n", 1);
	write(1, promt, ft_strlen(promt));
	free(promt);
}

static void	sig_quit(int signo)
{
	signo = 0;
	write(1, "\b\b  \b\b", 6);
	return ;
}

void	set_signal(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	return ;
}

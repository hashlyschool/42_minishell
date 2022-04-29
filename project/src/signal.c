/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:59:31 by hashly            #+#    #+#             */
/*   Updated: 2022/04/29 20:01:38 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_d(int signo)
{
	signo = 0;
	rl_clear_history();
	ft_putstr_fd("exit\n", STD_ERR);
	exit(0);
}

static void	sig_int(int signo)
{
	signo = 0;
	rl_replace_line("", 0);
	rl_done = 1;
}

static void	sig_quit(int signo)
{
	signo = 0;
	return ;
}

int	event(void )
{
	return (0);
}

void	set_signal(void)
{
	rl_outstream = stderr;
	rl_event_hook = event;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	return ;
}

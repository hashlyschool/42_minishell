/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:59:31 by hashly            #+#    #+#             */
/*   Updated: 2022/03/24 17:58:49 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Функция для обработки ^D
*/
void	sig_d(int signo)
{
	signo = 0;
	#ifdef __APPLE__
	clear_history();
	#elif __linux__
	rl_clear_history();
	ft_putstr_fd("exit\n", STD_OUT);
	#endif
	exit(0);
}

/*
Функция для обработки ^C
*/
static void	sig_int(int signo)
{
	signo = 0;
	// rl_replace_line("", 0);
	// rl_done = 1;
}

/*
Функция для обработки ^\
*/
static void	sig_quit(int signo)
{
	signo = 0;
	return ;
}

// static int	event(void )
// {
// 	return (0);
// }

/*
Функция для установки функций для перехвата окружения
*/
void	set_signal(void)
{
	// rl_event_hook = event;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:59:31 by hashly            #+#    #+#             */
/*   Updated: 2022/03/25 09:36:26 by hashly           ###   ########.fr       */
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
	#endif
	ft_putstr_fd("exit\n", STD_ERR);
	exit(0);
}

/*
Функция для обработки ^C
*/
static void	sig_int(int signo)
{
	signo = 0;
	rl_replace_line("", 0);
	#ifdef __linux__
	rl_done = 1;
	#elif __APPLE__
	ft_putstr_fd("\n", STD_ERR);
	ft_putstr_fd(rl_prompt, STD_ERR);
	#endif
}

/*
Функция для обработки ^\
*/
static void	sig_quit(int signo)
{
	signo = 0;
	return ;
}

#ifdef __linux__
int	event(void )
{
	return (0);
}
#endif

/*
Функция для установки функций для перехвата окружения
*/
void	set_signal(void)
{
	#ifdef __linux__
	rl_event_hook = event;
	#endif
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	return ;
}

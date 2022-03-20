/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:59:31 by hashly            #+#    #+#             */
/*   Updated: 2022/03/20 14:40:43 by hashly           ###   ########.fr       */
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
	#ifdef __APPLE__
	ft_putstr_fd("\n", STD_OUT);
	ft_putstr_fd(rl_prompt, STD_OUT);
	#elif __linux__
	ft_putstr_fd("\n", STD_OUT);
	ft_putstr_fd(rl_prompt, STD_OUT);
	#endif
}

/*
Функция для обработки ^\
*/
static void	sig_quit(int signo)
{
	signo = 0;
	#ifdef __APPLE__

	#elif __linux__
	ft_putstr_fd("\b\b  \b\b", STD_OUT);
	#endif
	return ;
}

/*
Функция для установки функций для перехвата окружения
*/
void	set_signal(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	return ;
}

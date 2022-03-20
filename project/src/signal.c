/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:59:31 by hashly            #+#    #+#             */
/*   Updated: 2022/03/19 20:40:00 by hashly           ###   ########.fr       */
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
	write(1, "exit\n", 5);
	clear_history();
	#elif __linux__
	rl_clear_history();
	write(1, "exit\n", 5);
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
	#define STR "\n"
	write(1, STR, ft_strlen(STR));
	write(1, rl_prompt, ft_strlen(rl_prompt));
	#elif __linux__
	write(1, "\n", 1);
	write(1, rl_prompt, ft_strlen(rl_prompt));
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
	write(1, "\b\b  \b\b", 6);
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

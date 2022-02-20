/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:59:31 by hashly            #+#    #+#             */
/*   Updated: 2022/02/19 17:52:49 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Функция для обработки ^D
*/
void	sig_d(int signo)
{
	signo = 0;
	write(1, "exit\n", 5);
	// rl_clear_history();
	exit(0);
}

/*
Функция для обработки ^C
*/
static void	sig_int(int signo)
{
	signo = 0;
	write(1, "\n", 1);
	write(1, rl_prompt, ft_strlen(rl_prompt));
}

/*
Функция для обработки ^\
*/
static void	sig_quit(int signo)
{
	signo = 0;
	write(1, "\b\b  \b\b", 6);
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

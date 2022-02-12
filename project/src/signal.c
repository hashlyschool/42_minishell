/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:59:31 by hashly            #+#    #+#             */
/*   Updated: 2022/02/12 15:59:38 by hashly           ###   ########.fr       */
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
	rl_clear_history();
	ft_free_envp();
	exit(0);
}

/*
Функция для обработки ^C
*/
static void	sig_int(int signo)
{
	char	*promt;

	signo = 0;
	promt = get_promt();
	write(1, "\n", 1);
	write(1, promt, ft_strlen(promt));
	free(promt);
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

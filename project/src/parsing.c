/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/02/12 20:54:29 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*
Функция для получения строки из терминала с помощью readline
promt - начальная строка aka bash
*/
static char	*get_line(void)
{
	char	*line_read;
	char	*promt;

	promt = get_promt();
	line_read = readline(promt);
	free(promt);
	if (line_read && *line_read)
		add_history (line_read);
	if (!line_read)
		sig_d(0);
	return (line_read);
}

/*
Эта функция разбивает строку str на составные части. В строках должна быть
информация следующего рода :
	cmd
	option or argv
	>	file_name
	>>	file_name
	<	file_name
	<<	file_name
	(
	)
	&&
	||
	|
	;
	${NAME}
	NULL

Т.к. аргумент может быть '(' или '< file_name' и т.д. Следует записать для
ключевых токенов особенные записи, чтобы в последующем не перепутать токены
и аргументы к команде. Поэтому в итоге нужно, чтобы
строка строк была в следующем виде:
	cmd
	option or argv
	\1\2>\3\23	file_name
	\1\2>>\3\23	file_name
	\1\2<\3\23	file_name
	\1\2<<\3\23	file_name
	\1\2(\3\23
	\1\2)\3\23
	\1\2&&\3\23
	\1\2||\3\23
	\1\2|\3\23
	\1\2;\3\23
	\001\002${NAME}\3\23
	NULL
*/
char	**split_str(char *str)
{
	return (ft_split(str, ' '));
}

/*
Функция для чтения с стандартного ввода команды с помощью readline, а затем
разбиения этой строки на составные части
*/
char	**parsing(void)
{
	char	*str;
	char	**ret;

	str = get_line(); //+
	ret = split_str(str); //- Masha
	free(str); //+
	return (ret);
}

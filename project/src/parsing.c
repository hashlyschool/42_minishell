/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/02/24 03:54:05 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Функция для получения строки из терминала с помощью readline
promt - начальная строка aka bash
*/
static char	*get_line(char **env)
{
	char	*line_read;
	char	*promt;

	promt = get_promt(env);
	line_read = readline(promt);
	free(promt);
	if (line_read && *line_read)
		add_history(line_read);
	if (!line_read)
	{
		ft_free_envp(env);
		sig_d(0);
	}
	return (line_read);
}

// char	*parce(char *str, char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'')
// 			str = ft_gap(str, &i);
// 		else if (str[i] == '\\')
// 			str = ft_slash(str, &i);
// 		else if (str[i] == '\"')
// 			str = ft_quotechar(str, &i);
// 		else if (str[i] == '$')
// 			str = ft_dollar(str, &i);
// 		else if (str[i] == '>')
// 			str = ft_dollar(str, &i);
// 		else if (str[i] == '<')
// 			ft_gap(str);
// 		else if (str[i] == '|')
// 			ft_gap(str);
// 		else if (str[i] == '(')
// 			ft_gap(str);
// 		else if (str[i] == '&')
// 			ft_gap(str);
// 		i++;
// 	}
// 	return (str);
// }

char	*parce(char *str, char **env)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			str = ft_gap(str, &i);
		else if (str[i] == '\\')
			str = ft_slash(str, &i);
		else if (str[i] == '\"')
			str = ft_quotechar(str, &i);
		else if (str[i] == '$')
			str = ft_dollar(str, &i, START_VALUE, END_VALUE);
		else if (str[i] == '(')
			str = ft_dollar(str, &i, BR_LEFT, BR_RIGHT);
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|'
			|| str[i] == '&')
			str = ft_replace(str, &i, str[i]);
		i++;
	}
	return (str);
}

/*
Masha
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
static char	**split_str(char *str, char **env)
{
	if (!env)
		;
	str = parce(str, env);
	printf("this is str %s\n",str);
	return (ft_split(str, ' '));
}

/* функция для посчета кавычек */

int	preparse(char *str)
{
	char	c;
	int		i;

	i = 0;
	c = '0';
	while (str[i])
	{
		if ((str[i] == '\'') || str[i] == '"')
		{
			if (!(i != 0 && str[i - 1] == '\\'))
			{
				if (c == str[i])
					c = '0';
				else if (c == '0')
					c = str[i];
			}
		}
		i++;
	}
	if (c != '0')
		return (0);
	return (1);
}

/*
Функция для чтения с стандартного ввода команды с помощью readline, а затем
разбиения этой строки на составные части
*/
char	**parsing(char **env)
{
	char	*str;
	char	**ret;

	str = get_line(env);
	if (!(preparse(str)))
		return (0);
	ret = split_str(str, env);
	free(str);
	return (ret);
}

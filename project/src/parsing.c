/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/03/13 18:42:33 by hashly           ###   ########.fr       */
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

void	ft_parse_split(t_parser *prs)
{
	if (prs->str)
		prs->mass = ft_add_line(prs->mass, prs->str);
	free(prs->str);
	prs->str = NULL;
}

char	*parce(char *str, t_parser *prs)
{
	int	i;

	i = 0;
	prs->str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			str = ft_gap(str, &i, prs);
		else if (str[i] == '\\')
			str = ft_slash(str, &i, prs);
		else if (str[i] == '\"')
			str = ft_quotechar(str, &i, prs);
		else if (str[i] == '$')
			str = ft_dollar(str, &i, START_VALUE, END_VALUE, prs);
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|'
			|| str[i] == '&' || str[i] == '*' || str[i] == ';' || str[i] == '('
			|| str[i] == ')')
			str = ft_replace(str, &i, str[i], prs);
		else if (str[i] == ' ')
		{
			if (prs->red == '>' || prs->red == '<')
				prs->str = ft_charjoin(prs->str, str[i]);
			else
				ft_parse_split(prs);
		}
		else
		{
			prs->str = ft_charjoin(prs->str, str[i]);
			prs->red = 0;
		}
		i++;
	}
	ft_parse_split(prs);
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
	t_parser	*prs;
	char		**ret;

	prs = malloc(sizeof(t_data));
	// prs->mass = (char **)malloc(sizeof(char *) * (1));
	prs->quo = 0;
	prs->red = 0;
	prs->mass = NULL;
	if (!env)
		;
	str = parce(str, prs);
	free(str);
	// printf("this is str %s\n", str);
	free(prs->str);
	// int i = 0;
	// while (prs->mass[i])
	// {
	// 	printf("this is mass [%s]\n", prs->mass[i]);
	// 	i++;
	// }
	ret = prs->mass;
	free (prs);
	return (ret);
}

/* функция для посчета кавычек */

int	preparse(char *str)
{
	char	c;
	int		i;
	int		c2;
	int		c3;
	int		dollar;

	i = 0;
	c = '0';
	c2 = 0;
	c3 = 0;
	dollar = 0;
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
		else if (str[i] == '(' || str[i] == ')' || str[i] == '{' || str[i] == '}')
		{
			if (str[i] == '(' && c == '0')
				c2++;
			else if (str[i] == ')' && c == '0')
				c2--;
			else if ((i != 0 && str[i - 1] == '$' && str[i] == '{' && c != '0')
				|| (str[i] == '{' && c == '0'))
			{
				if (str[i - 1] == '$')
					dollar = 1;
				c3++;
			}
			else if ((str[i] == '}' && c != '0' && dollar == 1)
				|| (str[i] == '}' && c == '0'))
			{
				c3--;
				dollar = 0;
			}
		}
		i++;
	}
	if (c != '0' || (c2 + c3) != 0)
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

	ret = NULL;
	str = get_line(env);
	if (!(preparse(str)))
		return (NULL);
	if (!(str[0]))
		ret = ft_add_line(ret, NULL);
	else
		ret = split_str(str, env);
	return (ret);
}

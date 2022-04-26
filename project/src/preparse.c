/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 22:42:34 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/26 22:57:48 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* функция для посчета кавычек */
char	preparse(char *str, t_preparse d)
{
	d.i = 0;
	d.c = '0';
	d.c2 = 0;
	d.c3 = 0;
	d.j = 0;
	d.let = 0;
	while (str[d.i])
	{
		if ((str[d.i] == '\'') || str[d.i] == '"' || str[d.i] == '\\')
		{
			if (!(d.i != 0 && str[d.i - 1] == '\\' && d.j != 1)
				&& str[d.i] != '\\')
			{
				if (d.c == str[d.i])
					d.c = '0';
				else if (d.c == '0')
					d.c = str[d.i];
				d.j = 0;
			}
			else if (d.i != 0 && str[d.i - 1] == '\\' && str[d.i] == '\\')
				d.j = 1;
		}
		else if (str[d.i] == '{' || str[d.i] == '}')
		{
			if (str[d.i] == '{' && d.c != '\'' && d.c != '\"')
				d.c3++;
			else if (str[d.i] == '}' && d.c != '\'' && d.c != '\"')
				d.c3--;
			d.c = str[d.i];
		}
		else if (str[d.i] == '(' || str[d.i] == ')')
		{
			if (str[d.i] == '(' && d.c != '\'' && d.c != '\"')
			{
				d.c2++;
				d.let = 0;
			}
			else if (str[d.i] == ')' && (d.c != '\'' && d.c != '\"')
				&& ((d.let > 0 && d.c2 > 0) || d.c2 == 0))
				d.c2--;
			d.c = str[d.i];
		}
		else if ((ft_strchr(" \r\v\n\t", str[d.i])) == NULL)
			d.let++;
		d.i++;
	}
	if (d.c3 != 0 || d.c2 != 0)
		return (d.c);
	return (0);
}

char	preparse_init(char *str)
{
	t_preparse	data;

	data.i = 0;
	data.c = '0';
	data.c2 = 0;
	data.c3 = 0;
	data.j = 0;
	data.let = 0;
	return (preparse(str, data));
}

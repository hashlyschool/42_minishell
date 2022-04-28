/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 22:42:34 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 00:43:55 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	preparse_1(char *str, t_preparse *d)
{
	if (!(d->i != 0 && str[d->i - 1] == '\\'
			&& d->j != 1) && str[d->i] != '\\')
	{
		if (d->c == str[d->i])
			d->c = '0';
		else if (d->c == '0')
			d->c = str[d->i];
		d->j = 0;
	}
	else if (d->i != 0 && str[d->i - 1] == '\\' && str[d->i] == '\\')
		d->j = 1;
}

void	preparse_2(char *str, t_preparse *d)
{
	if (str[d->i] == '(' && d->c != '\'' && d->c != '\"')
	{
		d->c2++;
		d->let = 0;
	}
	else if (str[d->i] == ')' && (d->c != '\'' && d->c != '\"')
		&& ((d->let > 0 && d->c2 > 0) || d->c2 == 0))
		d->c2--;
	d->c = str[d->i];
}

/* функция для посчета кавычек */
char	preparse(char *str, t_preparse d)
{
	while (str[d.i])
	{
		if ((str[d.i] == '\'') || str[d.i] == '"' || str[d.i] == '\\')
			preparse_1(str, &d);
		else if (str[d.i] == '{' || str[d.i] == '}')
		{
			if (str[d.i] == '{' && d.c != '\'' && d.c != '\"')
				d.c3++;
			else if (str[d.i] == '}' && d.c != '\'' && d.c != '\"')
				d.c3--;
			d.c = str[d.i];
		}
		else if (str[d.i] == '(' || str[d.i] == ')')
			preparse_2(str, &d);
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

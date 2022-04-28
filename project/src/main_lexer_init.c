/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 02:49:59 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 02:54:12 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer_true(char *str, t_lex_q *data)
{
	if (((data->error != NULL && data->error[1] == str[data->i])
			|| !(data->error)) && ft_strlen(data->error) != 2)
	{
		if (str[data->i] == ';' && data->ops == 1
			&& data->red == 0)
			;
		else
		{
			if (data->c == ';' && data->count_char == 1
				&& str[data->i] == ';' && data->ops != 1)
				data->error = ft_charjoin(data->error, str[data->i]);
			data->error = ft_charjoin(data->error, str[data->i]);
		}
	}
}

char	*lexer_init(char *str)
{
	t_lex_q	data;

	data.i = 0;
	data.error = NULL;
	data.red = 0;
	data.q = '0';
	data.w = 0;
	data.ops = 0;
	data.count_char = 0;
	data.spase = 0;
	return (lexer(str, &data));
}

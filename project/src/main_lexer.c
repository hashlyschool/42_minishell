/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 22:36:13 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 17:47:41 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer_spase(char *str, t_lex_q *data)
{
	data->c = str[data->i];
	if (data->error)
		free(data->error);
	data->error = NULL;
	data->spase = 0;
}

void	lexer_reset(t_lex_q *data)
{
	data->i--;
	data->w = 0;
}

void	lexer_que(char *str, t_lex_q *data)
{
	if (str[data->i] == data->q)
		data->q = '0';
	else
		data->q = str[data->i];
}

void	lexer_while(char *str, t_lex_q *data)
{
	if (ft_strchr(";&|", str[data->i]))
	{
		if (data->red == 0 || data->count_char > 1
			|| (data->count_char == 1 && data->c == ';')
			|| (data->spase == 1 && data->count_char == 1))
			lexer_true(str, data);
		else
			lexer_spase(str, data);
		data->count_char++;
	}
	else
	{
		if (data->c == ';' || (data->error != NULL
				&& data->error[0] == ';'))
			data->ops = 1;
		data->spase = 1;
	}
	data->i++;
	data->w = 1;
}

char	*lexer(char *str, t_lex_q *data)
{
	while (str[data->i] != '\0')
	{
		data->c = 0;
		data->count_char = 0;
		data->ops = 0;
		while (ft_strchr(";& \r\v\n\t|<>", str[data->i]) != NULL
			&& data->q == '0' && str[data->i] != '\0')
			lexer_while(str, data);
		if (data->c != 0)
			data->red = 0;
		if (str[data->i] == '\"' || str[data->i] == '\'')
			lexer_que(str, data);
		else if (str[data->i] != '\0')
			data->red++;
		if (data->w == 1)
			lexer_reset(data);
		data->i++;
	}
	if ((data->error != NULL && str[data->i] == '\0'))
		return (ft_strjoin_free_s2(SYN_ERR, \
		ft_strjoin_free_s1(data->error, "\'\n")));
	if ((data->c != ';' && data->c != 0 && data->red != 1))
		return (ft_strdup(END_ERR));
	return (NULL);
}

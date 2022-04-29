/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 02:58:10 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/29 20:08:47 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_slash(char *str, int *i, t_parser *prs)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0,*i);
	tmp2 = ft_strdup(str + *i + 1);
	if (str[(*i) + 1] && str[(*i) + 1] == ' ')
		prs->str = ft_strjoin_free_s1(prs->str, START_DOUBLE_QUOTE);
	if (prs->quo != 1 && (str[*i + 1]) != '\0')
		prs->str = ft_charjoin(prs->str, str[*i + 1]);
	if (str[(*i) + 1] && str[(*i) + 1] == ' ')
		prs->str = ft_strjoin_free_s1(prs->str, END_DOUBLE_QUOTE);
	tmp = ft_strjoin_free_all(tmp, tmp2);
	if (str[(*i) + 1] == '\0')
		--(*i);
	free(str);
	return (tmp);
}

void	init_dollar(t_dollar *data, int *i)
{
	data->flag = 0;
	data->plus = 1;
	data->index = -1;
	data->end = 0;
	data->j = *i;
}

char	*ft_dollar_1(char *str, int *i, t_parser *prs, t_dollar *data)
{
	data->tmp = ft_substr(str, 0, data->j);
	if (str[data->j] == '$' && str[data->j + 1] == '{')
		data->tmp2 = ft_substr(str, data->j + 2, (*i) - data->j - 2);
	else
		data->tmp2 = ft_substr(str, data->j + 1, (*i) - data->j - 1);
	if (ft_strchr("?!", str[(*i) - 1]) || (str[(*i)] == '$' && !data->index))
		(*i)--;
	data->tmp3 = ft_strdup(str + (*i) + data->plus);
	data->tmp2 = ft_strjoin_free_s2(START_VALUE, data->tmp2);
	data->tmp2 = ft_strjoin_free_s1(data->tmp2, END_VALUE);
	if (prs->quo == 0)
		prs->str = ft_strjoin_free_s1(prs->str, data->tmp2);
	data->tmp = ft_strjoin_free_s1(data->tmp, data->tmp2);
	data->tmp = ft_strjoin_free_s1(data->tmp, data->tmp3);
	free(data->tmp2);
	free(data->tmp3);
	if (str[data->j] == '$' && str[data->j + 1] == '{')
		(*i) += ft_strlen(START_VALUE) + ft_strlen(END_VALUE) - 3;
	else if (str[data->j + 1] == '?')
		(*i) += ft_strlen(START_VALUE) + ft_strlen(END_VALUE) - 1;
	else
		(*i) += ft_strlen(START_VALUE) + ft_strlen(END_VALUE) - 2;
	free(str);
	return (data->tmp);
}

char	*ft_dollar_2(char *str, int *i, t_parser *prs)
{
	prs->str = ft_charjoin(prs->str, '$');
	if (str[(*i)] != '\0' && str[(*i)] != '\\')
		prs->str = ft_charjoin(prs->str, str[(*i)]);
	return (str);
}

char	*ft_dollar(char *str, int *i, t_parser *prs)
{
	t_dollar	data;

	init_dollar(&data, i);
	if (str[data.j + 1] == '{')
		data.flag = 1;
	while ((str[(*i)++]))
	{
		data.index += 1;
		if (!(data.flag) && !(data.index) && ft_isdigit(str[(*i)]))
			data.end = 1;
		if ((!ft_isdigit(str[(*i)]) && !ft_isalpha(str[(*i)]) && data.flag == 0
				&& str[(*i)] != '_' && str[(*i)] != '?')
			|| data.end == 1)
			data.plus = 0;
		if (str[(*i)] == '}' || str[(*i)] == '?'
			|| ft_strchr("$?!", str[(*i)]) || data.plus == 0)
			break ;
	}
	if ((data.index == -1 || (data.plus == 0
				&& data.index == 0)) && data.end != 1)
		return (ft_dollar_2(str, i, prs));
	if ((ft_strchr("?!", str[(*i)]) && str[(*i)] != '\0') || data.end == 1
		|| (str[(*i)] == '$' && !data.index))
		(*i)++;
	return (ft_dollar_1(str, i, prs, &data));
}

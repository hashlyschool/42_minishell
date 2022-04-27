/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:49:18 by a79856            #+#    #+#             */
/*   Updated: 2022/04/27 02:20:07 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_gap(char *str, int *i, t_parser *prs)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1,*i - j - 1);
	if (tmp2[0] == '\0' || str[(*i) + 1] != '\0' || str[(*i) + 1] == ' ')
		prs->spase = 1;
	prs->str = ft_strjoin_free_s1(prs->str, tmp2);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin_free_s1(tmp, tmp2);
	tmp = ft_strjoin_free_s1(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	free(str);
	*i -= 2;
	return (tmp);
}

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

char	*ft_quotechar_1(char *str, int *i, t_parser *prs)
{
	prs->quo = 1;
	if (prs->d_quo != 1)
		prs->str = ft_strjoin_free_s1(prs->str, START_DOUBLE_QUOTE);
	str = ft_dollar(str, i, prs);
	prs->d_quo = 1;
	prs->quo = 0;
	return (str);
}

char	*ft_quotechar_2(char *str, int *i, t_parser *prs)
{
	prs->quo = 1;
	str = ft_slash(str, i, prs);
	prs->quo = 0;
	return (str);
}

char	*ft_quotechar_3(char *str, int *i, t_parser *prs, int j)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, (*i) - j - 1);
	if (tmp2[0] == '\0' || str[(*i) + 1] != '\0' || str[(*i) + 1] == ' ')
		prs->spase = 1;
	tmp3 = ft_strdup(str + (*i) + 1);
	tmp = ft_strjoin_free_s1(tmp, tmp2);
	tmp = ft_strjoin_free_s1(tmp, tmp3);
	prs->str = ft_strjoin_free_s1(prs->str, tmp2);
	if (prs->d_quo == 1)
		prs->str = ft_strjoin_free_s1(prs->str, END_DOUBLE_QUOTE);
	free(tmp2);
	free(tmp3);
	free(str);
	(*i) -= 2;
	return (tmp);
}

char	*ft_quotechar(char *str, int *i, t_parser *prs)
{
	int		j;

	j = *i;
	prs->d_quo = 0;
	while (str[(*i)++])
	{
		if (str[(*i)] == '$' && (str[(*i) + 1] != '\0')
			&& (ft_isalnum(str[(*i) + 1])
				|| ft_strchr("$_?!", str[(*i) + 1])))
			str = ft_quotechar_1(str, i, prs);
		if (str[(*i)] == '\\' && (str[(*i) + 1] == '\"'
				|| str[(*i) + 1] == '$' || str[(*i) + 1] == '\\'))
			str = ft_quotechar_2(str, i, prs);
		else if (str[(*i)] == '\"')
			break ;
	}
	return (ft_quotechar_3(str, i, prs, j));
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
	data->tmp3 = ft_strdup(str + (*i) + data->plus);
	if (ft_strchr("?!", str[(*i) - 1]) || (str[(*i)] == '$' && !data->index))
		(*i)--;
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

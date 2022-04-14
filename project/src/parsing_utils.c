/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:49:18 by a79856            #+#    #+#             */
/*   Updated: 2022/04/14 16:52:47 by a79856           ###   ########.fr       */
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
	tmp = ft_strjoin_free_all(tmp, tmp2);
	free(str);
	if  (str[(*i) + 1] == '\0')
		--(*i);
	return (tmp);
}

char	*ft_quotechar(char *str, int *i, t_parser *prs)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	prs->d_quo = 0;
	while (str[(*i)++])
	{
		if (str[(*i)] == '$' && (str[(*i) + 1] != '\0') && (ft_isalnum(str[(*i) + 1])
			|| ft_strchr("$_?!", str[(*i) + 1])))
		{
			prs->quo = 1;
			if (prs->d_quo != 1)
				prs->str = ft_strjoin_free_s1(prs->str, START_DOUBLE_QUOTE);
			str = ft_dollar(str, i, prs);
			prs->d_quo = 1;
			prs->quo = 0;
		}
		if (str[(*i)] == '\\' && (str[(*i) + 1] == '\"'
				|| str[(*i) + 1] == '$' || str[(*i) + 1] == '\\'))
		{
			prs->quo = 1;
			str = ft_slash(str, i, prs);
			prs->quo = 0;
		}
		else if (str[(*i)] == '\"')
			break ;
	}
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


void	init_dollar(t_dollar *data)
{
	data->flag = 0;
	data->plus = 1;
	data->index = -1;
	data->end = 0;
}

char	*ft_dollar(char *str, int *i, t_parser *prs)
{
	int			j;
	char		*tmp;
	char		*tmp2;
	char		*tmp3;
	t_dollar	data;

	init_dollar(&data);
	j = *i;
	/* Поставить флаг какой это доллар, исходя из этого запускать проверку*/
	if (str[j + 1] == '{')
		data.flag = 1;
	while ((str[(*i)++]))
	{
		data.index += 1;
		if (!(data.flag) && !(data.index) && ft_isdigit(str[(*i)]))
			data.end = 1;
		if ((!ft_isdigit(str[(*i)]) && !ft_isalpha(str[(*i)]) && data.flag == 0
			&& str[(*i)] != '_'  && str[(*i)] != '?') || data.end == 1)
			data.plus = 0;
		// if ((str[(*i)] == '}') || (str[(*i)] == '?' && data.flag == 0)
		if (str[(*i)] == '}' || str[(*i)] == '?'
			|| ft_strchr("$?!", str[(*i)]) || data.plus == 0)
			break ;
	}
	if ((data.index == -1 || (data.plus == 0 && data.index == 0)) && data.end != 1)
	{
		prs->str = ft_charjoin(prs->str,'$');
		prs->str = ft_charjoin(prs->str,str[(*i)]);
		return (str);
	}
	if ((ft_strchr("?!", str[(*i)]) && str[(*i)] != '\0') || data.end == 1 ||
		(str[(*i)] == '$' && !data.index))
		{
			(*i)++;
			printf("\nlol\n");
		}
	tmp = ft_substr(str, 0, j);
	if (str[j] == '$' && str[j + 1] == '{')
		tmp2 = ft_substr(str, j + 2, (*i) - j - 2);
	else
		tmp2 = ft_substr(str, j + 1, (*i) - j - 1);
	tmp3 = ft_strdup(str + (*i) + data.plus);
	if (ft_strchr("?!", str[(*i) - 1])|| (str[(*i)] == '$' && !data.index))
		(*i)--;
	tmp2 = ft_strjoin_free_s2(START_VALUE, tmp2);
	// if (prs->quo == 1)
	// {
	// 	tmp2 = ft_strjoin_free_s2(START_DOUBLE_QUOTE, tmp2);
	// 	prs->d_quo = 1;
	// }
	tmp2 = ft_strjoin_free_s1(tmp2, END_VALUE);
	if (prs->quo == 0)
		prs->str = ft_strjoin_free_s1(prs->str, tmp2);
	tmp = ft_strjoin_free_s1(tmp, tmp2);
	tmp = ft_strjoin_free_s1(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	if (str[j] == '$' && str[j + 1] == '{')
		(*i) += ft_strlen(START_VALUE) + ft_strlen(END_VALUE) - 3;
	else
		(*i) += ft_strlen(START_VALUE) + ft_strlen(END_VALUE) - 1;
	free(str);
	return (tmp);
}

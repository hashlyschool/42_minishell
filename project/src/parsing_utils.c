/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:49:18 by a79856            #+#    #+#             */
/*   Updated: 2022/03/20 15:25:43 by a79856           ###   ########.fr       */
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
	prs->str = ft_charjoin(prs->str, str[*i + 1]);
	tmp = ft_strjoin_free_all(tmp, tmp2);
	free(str);
	// ++(i);
	return (tmp);
}

char	*ft_quotechar(char *str, int *i, t_parser *prs)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[(*i)++])
	{
		if (str[(*i)] == '$')
		{
			prs->quo = 1;
			str = ft_dollar(str, i, prs);
			prs->quo = 0;
		}
		if (str[(*i)] == '\\' && (str[(*i) + 1] == '\"'
				|| str[(*i) + 1] == '$' || str[(*i) + 1] == '\\'))
			str = ft_slash(str, i, prs);
		if (str[(*i)] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	printf("tmp %s\n",tmp);
	tmp2 = ft_substr(str, j + 1, (*i) - j - 1);
	printf("tmp2 %s\n",tmp2);
	tmp3 = ft_strdup(str + (*i) + 1);
	printf("tmp3 %s\n",tmp3);
	tmp = ft_strjoin_free_s1(tmp, tmp2);
	tmp = ft_strjoin_free_s1(tmp, tmp3);
	prs->str = ft_strjoin_free_s1(prs->str, tmp2);
	free(tmp2);
	free(tmp3);
	free(str);
	(*i) -= 2;
	printf("%s\n",tmp);
	return (tmp);
}

void	dollar_data(t_dollars *data)
{
	data->plus = 1;
	data->flag = 0;
	data->num = 0;
	data->start = ft_strdup(START_VALUE);
	data->end = ft_strdup(END_VALUE);
}

char	*ft_dollar(char *str, int *i, t_parser *prs)
{
	t_dollars	data;
	int			j;
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	j = *i;
	dollar_data(&data);
	/* Поставить флаг какой это доллар, исходя из этого запускать проверку*/
	if (str[j + 1] == '{')
		data.flag = 1;
	while ((str[(*i)++]))
	{
		if ((! ft_isalnum(str[(*i)]) && str[(*i)]
			!= '_' && data.flag == 0) || (str[(*i)] == '?'))
			data.plus = 0;
		if ((str[(*i)] == '}') || data.plus == 0 || (data.num > 0 && ft_isdigit(str[(*i)])))
			break ;
		data.num += 1;
	}
	printf("%c \n",str[(*i)]);
	tmp = ft_substr(str, 0, j);
	if (str[j] == '$' && str[j + 1] == '{')
		tmp2 = ft_substr(str, j + 2, *i - j - 2);
	else
		tmp2 = ft_substr(str, j + 1, (*i) - j);
	tmp3 = ft_strdup(str + (*i) + 1);
	if (data.flag == 0)
	{
		data.start = ft_strdup(START_DOLLAR);
		data.end = ft_strdup(END_DOLLAR);
	}
	if (data.num > 0)
	{
		tmp2 = ft_strjoin_free_s2(data.start, tmp2);
		tmp2 = ft_strjoin_free_s1(tmp2, data.end);
		if (prs->quo == 0)
			prs->str = ft_strjoin_free_s1(prs->str, tmp2);
	}
	tmp = ft_strjoin_free_s1(tmp, tmp2);
	tmp = ft_strjoin_free_s1(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	if (str[j] == '$' && str[j + 1] == '{')
		(*i) += ft_strlen(data.start) + ft_strlen(data.end) - 3;
	else
		(*i) += ft_strlen(data.start) + ft_strlen(data.end) - 1;
	free(str);
	return (tmp);
}

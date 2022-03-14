/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:49:18 by a79856            #+#    #+#             */
/*   Updated: 2022/03/15 00:02:34 by sstyx            ###   ########.fr       */
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
			str = ft_dollar(str, i, START_VALUE, END_VALUE, prs);
			prs->quo = 0;
		}
		if (str[(*i)] == '\\' && (str[(*i) + 1] == '\"'
				|| str[(*i) + 1] == '$' || str[(*i) + 1] == '\\'))
			str = ft_slash(str, i, prs);
		if (str[(*i)] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, (*i) - j - 1);
	tmp3 = ft_strdup(str + (*i) + 1);
	tmp = ft_strjoin_free_s1(tmp, tmp2);
	tmp = ft_strjoin_free_s1(tmp, tmp3);
	prs->str = ft_strjoin_free_s1(prs->str, tmp2);
	free(tmp2);
	free(tmp3);
	free(str);
	(*i) -= 2;
	return (tmp);
}

char	*ft_dollar(char *str, int *i, char *start, char *end, t_parser *prs)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	// if (str[j] == '$' && str[(*i + 1)] != '{')
	// 	return (str);
	while ((str[(*i)++]))
	{
		if ((str[j] == '$' && str[(*i)] == '}') || (str[(*i)] == ' ' && str[j + 1] != '{' ))
			break ;
	}
	tmp = ft_substr(str, 0, j);
	if (str[j] == '$' && str[j + 1] == '{')
		tmp2 = ft_substr(str, j + 2, *i - j - 2);
	else
		tmp2 = ft_substr(str, j + 1, (*i) - j - 1);
	tmp3 = ft_strdup(str + (*i) + 1);
	tmp2 = ft_strjoin_free_s2(start, tmp2);
	tmp2 = ft_strjoin_free_s1(tmp2, end);
	if (prs->quo == 0)
		prs->str = ft_strjoin_free_s1(prs->str, tmp2);
	tmp = ft_strjoin_free_s1(tmp, tmp2);
	tmp = ft_strjoin_free_s1(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	(*i) += ft_strlen(start) + ft_strlen(end) - 3;
	free(str);
	return (tmp);
}

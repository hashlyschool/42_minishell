/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:49:18 by a79856            #+#    #+#             */
/*   Updated: 2022/04/27 02:59:19 by sstyx            ###   ########.fr       */
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

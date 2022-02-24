/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:49:18 by a79856            #+#    #+#             */
/*   Updated: 2022/02/24 03:54:06 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_gap(char *str, int *i)
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
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	// free(str);
	free(tmp2);
	free(tmp3);
	*i -= 2;
	return (tmp);
}

char	*ft_slash(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0,*i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	// free(str);
	// ++(i);
	return (tmp);
}

char	*ft_quotechar(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[(*i)++])
	{
		if (str[*i] == '\\' && (str[(*i) + 1] == '\"'
				|| str[(*i) + 1] == '$' || str[(*i) + 1] == '\\'))
			str = ft_slash(str, i);
		if (str[(*i)] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp2);
	// free(str);
	free(tmp3);
	*i -= 2;
	return (tmp);
}

char	*ft_dollar(char *str, int *i, char *start, char *end)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	if (str[j] == '$' && str[(*i + 1)] != '{')
		return (str);
	while ((str[(*i)++]))
	{
		if ((str[j] == '$' && str[(*i)] == '}')
			|| (str[j] == '(' && str[(*i)] == ')'))
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	if (str[j]== '$')
		tmp2 = ft_substr(str, j + 2, *i - j - 2);
	tmp3 = ft_strdup(str + *i + 1);
	tmp2 = ft_strjoin(start, tmp2);
	tmp2 = ft_strjoin(tmp2, end);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	free(tmp2);
	free(tmp3);
	*i += ft_strlen(start) + ft_strlen(end);
	return (tmp);
}

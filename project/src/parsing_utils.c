/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:49:18 by a79856            #+#    #+#             */
/*   Updated: 2022/02/20 20:25:13 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_gap(char *str, int i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = i;
	while (str[++(i)])
	{
		if (str[(i)] == '\'')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, i - j - 1);
	tmp3 = ft_strdup(str + i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	// free(str);
	free(tmp2);
	free(tmp3);
	return (tmp);
}

char	*ft_slash(char *str, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, i);
	tmp2 = ft_strdup(str + i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	// free(str);
	++(i);
	return (tmp);
}

char	*ft_quotechar(char *str, int i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	if (env)
		;
	j = i;
	while (str[(i)++])
	{
		if (str[(i)] == '\\' && (str[(i) + 1] == '\"'
				|| str[(i) + 1] == '$' || str[(i) + 1] == '\\'))
			str = ft_slash(str, i);
		if (str[(i)] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j - 1);
	tmp2 = ft_substr(str, j + 1, i - j - 1);
	tmp3 = ft_strdup(str + i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
	// printf("quo_str = %s\n", tmp);
	free(tmp2);
	// free(str);
	free(tmp3);
	return (tmp);
}

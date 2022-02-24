/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_replase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 03:08:16 by a79856            #+#    #+#             */
/*   Updated: 2022/02/24 03:12:27 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_replace_util(char *str, int *i, int flag, char *start)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + flag);
	tmp2 = ft_strjoin(start, tmp2);
	tmp = ft_strjoin(tmp, tmp2);
	free(tmp2);
	*i += ft_strlen(start);
	return (tmp);
}

char	*ft_replace(char *str, int *i, char c)
{
	int		j;
	int		flag;
	char	*tmp;

	j = *i;
	flag = 0;
	if (str[(*i + 1)] == c && c != ';')
		flag = 1;
	if (c == '>' && flag == 1)
		tmp = ft_replace_util(str, i, flag + 1, REDIR_RIGHT_TWO);
	else if (c == '>' && flag == 0)
		tmp = ft_replace_util(str, i, flag + 1, REDIR_RIGHT_ONE);
	else if (c == '<' && flag == 1)
		tmp = ft_replace_util(str, i, flag + 1, REDIR_LEFT_TWO);
	else if (c == '<' && flag == 0)
		tmp = ft_replace_util(str, i, flag + 1, REDIR_LEFT_ONE);
	else if (c == '&' && flag == 1)
		tmp = ft_replace_util(str, i, flag + 1, AND_STR);
	else if (c == '|' && flag == 1)
		tmp = ft_replace_util(str, i, flag + 1, OR_STR);
	else if (c == '|' && flag == 0)
		tmp = ft_replace_util(str, i, flag + 1, PIPE_STR);
	else if (c == ';' && flag == 0)
		tmp = ft_replace_util(str, i, flag + 1, SEMICOLON);
	return (tmp);
}

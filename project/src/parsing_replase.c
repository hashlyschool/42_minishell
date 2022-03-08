/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_replase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 03:08:16 by a79856            #+#    #+#             */
/*   Updated: 2022/03/05 02:12:11 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* функция для посимвольного добаления в строку*/
char	*ft_charjoin(char *str, char c)
{
	char	*ptr;
	size_t	len;
	char	*tmp;

	if (!str || !c)
		return (NULL);
	len = ft_strlen(str) + 1;
	ptr = (char *)malloc(sizeof(*str) * (len + 1));
	if (!ptr)
		return (NULL);
	tmp = str;
	while (*str)
		*ptr++ = *str++;
	*ptr++ = c;
	*ptr = 0;
	free(tmp);
	return (ptr - len);
}

/* продолжение функции для замены & > >> | */
char	*ft_replace_util(char *str, int *i, int flag, char *start, t_parser *prs)
{
	char	*tmp;
	char	*tmp2;
	int		j;

	j = *i;
	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + flag);
	prs->str = ft_strjoin(prs->str, start);
	tmp2 = ft_strjoin(start, tmp2);
	tmp = ft_strjoin(tmp, tmp2);
	*i += ft_strlen(start) - 1;
	free(tmp2);
	return (tmp);
}

/* функции для замены & > >> | */
char	*ft_replace(char *str, int *i, char c, t_parser *prs)
{
	int		j;
	int		flag;
	char	*tmp;

	j = *i;
	flag = 0;
	tmp = NULL;
	prs->red = c;
	if (str[(*i + 1)] == c && c != ';')
		flag = 1;
	if (c == '>' && flag == 1)
		tmp = ft_replace_util(str, i, flag + 1, REDIR_RIGHT_TWO, prs);
	else if (c == '>' && flag == 0)
		tmp = ft_replace_util(str, i, flag + 1, REDIR_RIGHT_ONE, prs);
	else if (c == '<' && flag == 1)
		tmp = ft_replace_util(str, i, flag + 1, REDIR_LEFT_TWO, prs);
	else if (c == '<' && flag == 0)
		tmp = ft_replace_util(str, i, flag + 1, REDIR_LEFT_ONE, prs);
	else if (c == '&' && flag == 1)
		tmp = ft_replace_util(str, i, flag + 1, AND_STR, prs);
	else if (c == '|' && flag == 1)
		tmp = ft_replace_util(str, i, flag + 1, OR_STR, prs);
	else if (c == '|' && flag == 0)
		tmp = ft_replace_util(str, i, flag + 1, PIPE_STR, prs);
	else if (c == ';' && flag == 0)
		tmp = ft_replace_util(str, i, flag + 1, SEMICOLON, prs);
	return (tmp);
}

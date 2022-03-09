/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_replase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 03:08:16 by a79856            #+#    #+#             */
/*   Updated: 2022/03/09 16:31:10 by hashly           ###   ########.fr       */
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
	int		j;

	j = *i;
	tmp = ft_substr(str, 0, *i);
	tmp = ft_strjoin_free_s1(tmp, start);
	tmp = ft_strjoin_free_all(tmp, ft_strdup(str + *i + flag));
	prs->str = ft_strjoin_free_s1(prs->str, start);
	*i += ft_strlen(start) - 1;
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

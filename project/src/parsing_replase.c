/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_replase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 03:08:16 by a79856            #+#    #+#             */
/*   Updated: 2022/04/26 23:20:34 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_fd(char *str, int i)
{
	int		a;
	char	*num;

	a = 0;
	num = NULL;
	while (ft_isdigit(str[i]))
	{
		i--;
		a++;
	}
	num = ft_substr(str, i + 1, a);
	a = ft_atoi(num);
	free(num);
	if (a > MAX_FD)
		;//выдать ошибку
	if (str[i] == ' ' && a >= 0)
		return (i + 1);
	return (-1);
}

/* продолжение функции для замены & > >> | */
char	*ft_replace_util(char *str, int *i, int flag, char *start, t_parser *prs)
{
	char	*tmp;
	int		j;
	char	*str2;
	int		len;
	int		len_prs;

	j = *i;
	tmp = ft_substr(str, 0, *i);
	str2 = str;
	tmp = ft_strjoin_free_s1(tmp, start);
	len_prs = 0;
	if (str[*i + flag] != '\0')
		tmp = ft_strjoin_free_all(tmp, ft_strdup(str + *i + flag));
	if (str[(*i)] == '>')
	{
		if (prs->r == 1)
			prs->r = 0;
		else
			prs->r = 1;
	}
	len = ft_is_fd(str, (*i) - 1);
	if (len != (*i) && len != -1)
	{
		len_prs = ft_strlen(prs->str);
		free(prs->str);
		prs->str = ft_substr(str, len - len_prs + 1, len - (len - len_prs + 1));
		ft_parse_split(prs);
		prs->str = ft_substr(str, len, (*i) - len);
	}
	if (prs->r == 0 || len == (*i) || len == -1)
		ft_parse_split(prs);
	if (str[(*i)] != '>' && str[(*i)] != '<' && str[(*i)] != '*')
	{
		if (prs->str && prs->str[0])
			ft_parse_split(prs);
		free(prs->str);
		prs->str = ft_strdup(start);
		ft_parse_split(prs);
		free(prs->str);
		prs->str = NULL;
	}
	else
		prs->str = ft_strjoin_free_s1(prs->str, start);
	*i += ft_strlen(start) - 1;
	free(str);
	return (tmp);
}

void	ft_replase_continue(char *str, int *i, t_replase *t, t_parser *prs)
{
	if (t->c == '<' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, t->flag + 1, REDIR_LEFT_ONE, prs);
	else if (t->c == '&' && t->flag == 1)
		t->tmp = ft_replace_util(str, i, t->flag + 1, AND_STR, prs);
	else if (t->c == '|' && t->flag == 1)
		t->tmp = ft_replace_util(str, i, t->flag + 1, OR_STR, prs);
	else if (t->c == '|' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, t->flag + 1, PIPE_STR, prs);
	else if (t->c == ';' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, t->flag + 1, SEMICOLON, prs);
	else if (t->c == '*' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, t->flag + 1, STAR, prs);
	else if (t->c == '(' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, t->flag + 1, BR_LEFT, prs);
	else if (t->c == ')' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, t->flag + 1, BR_RIGHT, prs);
}

/* функции для замены & > >> | */
char	*ft_replace(char *str, int *i, char c, t_parser *prs)
{
	t_replase	t;

	t.j = *i;
	t.flag = 0;
	t.tmp = NULL;
	t.c = c;
	prs->red = c;
	if (str[(*i + 1)] == c && c != ';' && c != '(' && c != ')' && c != '*')
		t.flag = 1;
	if (c == '>' && t.flag == 1)
		t.tmp = ft_replace_util(str, i, t.flag + 1, REDIR_RIGHT_TWO, prs);
	else if (c == '>' && t.flag == 0)
		t.tmp = ft_replace_util(str, i, t.flag + 1, REDIR_RIGHT_ONE, prs);
	else if (c == '<' && t.flag == 1)
		t.tmp = ft_replace_util(str, i, t.flag + 1, REDIR_LEFT_TWO, prs);
	else if (ft_strchr("<&|;*()", c))
		ft_replase_continue(str, i, &t, prs);
	else
	{
		prs->str = ft_charjoin(prs->str, c);
		free(t.tmp);
		return (str);
	}
	return (t.tmp);
}

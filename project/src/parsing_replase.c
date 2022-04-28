/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_replase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 03:08:16 by a79856            #+#    #+#             */
/*   Updated: 2022/04/27 00:17:28 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//выдать ошибку в 31 строчке
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
		;
	if (str[i] == ' ' && a >= 0)
		return (i + 1);
	return (-1);
}

void	ft_replase_continue(char *str, int *i, t_replase *t)
{
	if (t->c == '<' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, REDIR_LEFT_ONE, t);
	else if (t->c == '&' && t->flag == 1)
		t->tmp = ft_replace_util(str, i, AND_STR, t);
	else if (t->c == '|' && t->flag == 1)
		t->tmp = ft_replace_util(str, i, OR_STR, t);
	else if (t->c == '|' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, PIPE_STR, t);
	else if (t->c == ';' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, SEMICOLON, t);
	else if (t->c == '*' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, STAR, t);
	else if (t->c == '(' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, BR_LEFT, t);
	else if (t->c == ')' && t->flag == 0)
		t->tmp = ft_replace_util(str, i, BR_RIGHT, t);
}

/* функции для замены & > >> | */
char	*ft_replace(char *str, int *i, char c, t_parser *prs)
{
	t_replase	t;

	t.j = *i;
	t.flag = 0;
	t.tmp = NULL;
	t.c = c;
	t.p = prs;
	prs->red = c;
	if (str[(*i + 1)] == c && c != ';' && c != '(' && c != ')' && c != '*')
		t.flag = 1;
	if (c == '>' && t.flag == 1)
		t.tmp = ft_replace_util(str, i, REDIR_RIGHT_TWO, &t);
	else if (c == '>' && t.flag == 0)
		t.tmp = ft_replace_util(str, i, REDIR_RIGHT_ONE, &t);
	else if (c == '<' && t.flag == 1)
		t.tmp = ft_replace_util(str, i, REDIR_LEFT_TWO, &t);
	else if (ft_strchr("<&|;*()", c))
		ft_replase_continue(str, i, &t);
	else
	{
		prs->str = ft_charjoin(prs->str, c);
		free(t.tmp);
		return (str);
	}
	return (t.tmp);
}

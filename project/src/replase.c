/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replase.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:11:29 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/28 11:51:04 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_replace_len(char *str, int *i, t_rep_utils *rep, t_replase *t)
{
	rep->len_prs = ft_strlen(t->p->str);
	free(t->p->str);
	t->p->str = ft_substr(str, rep->len,
			rep->len - (rep->len));
	ft_parse_split(t->p);
	t->p->str = ft_substr(str, rep->len, (*i) - rep->len);
}

void	ft_replace_red(char *start, t_replase *t)
{
	if (t->p->str && t->p->str[0])
		ft_parse_split(t->p);
	free(t->p->str);
	t->p->str = ft_strdup(start);
	ft_parse_split(t->p);
	free(t->p->str);
	t->p->str = NULL;
}

void	ft_replace_flag(t_replase *t)
{
	if (t->p->r == 1)
		t->p->r = 0;
	else
		t->p->r = 1;
}

/* продолжение функции для замены & > >> | */
char	*ft_replace_util(char *str, int *i, char *start, t_replase *t)
{
	t_rep_utils	rep;

	t->flag += 1;
	rep.j = *i;
	rep.tmp = ft_substr(str, 0, *i);
	rep.str2 = str;
	rep.tmp = ft_strjoin_free_s1(rep.tmp, start);
	rep.len_prs = 0;
	if (str[*i + t->flag] != '\0')
		rep.tmp = ft_strjoin_free_all(rep.tmp, ft_strdup(str + *i + t->flag));
	if (str[(*i)] == '>')
		ft_replace_flag(t);
	rep.len = ft_is_fd(str, (*i) - 1);
	if (rep.len != (*i) && rep.len != -1)
		ft_replace_len(str, i, &rep, t);
	if ((t->p->r == 0 || rep.len == (*i)
			|| rep.len == -1) && str[(*i)] != '*')
		ft_parse_split(t->p);
	if (str[(*i)] != '>' && str[(*i)] != '<' && str[(*i)] != '*')
		ft_replace_red(start, t);
	else
		t->p->str = ft_strjoin_free_s1(t->p->str, start);
	*i += ft_strlen(start) - 1;
	free(str);
	return (rep.tmp);
}

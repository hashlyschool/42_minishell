/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_check_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 02:33:00 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 02:45:07 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	chack_redirect_1(t_red *r)
{
	r->red = 0;
	r->start = 0;
	r->red = 0;
}

void	chack_redirect_2(char *str, t_red *r)
{
	if (str[r->i] == r->q)
		r->q = '0';
	else
		r->q = str[r->i];
}

char	*check_redirect(char *str, t_red *r)
{
	while (str[r->i] != '\0')
	{
		if (r->start > 0 && r->red > 0 && r->red > 0)
			chack_redirect_1(r);
		while (ft_strchr(">< \r\v\n\t", str[r->i]) != NULL
			&& r->q == '0' && str[r->i] != '\0')
		{
			if (ft_strchr("<>", str[r->i]))
				r->red++;
			r->i++;
		}
		if (str[r->i] == '\"' || str[r->i] == '\'')
			chack_redirect_2(str, r);
		if (str[r->i] == '\0')
			break ;
		if (r->red == 0)
			r->start++;
		else
			r->red++;
		r->i++;
	}
	if (r->red > 0 && ((r->red == 0 && r->red == 0) || r->red == 0))
		return (TOK_ERR);
	return (NULL);
}

char	*init_check_red(char *str)
{
	t_red	r;

	r.i = 0;
	r.red = 0;
	r.start = 0;
	r.finish = 0;
	r.q = '0';
	return (check_redirect(str, &r));
}

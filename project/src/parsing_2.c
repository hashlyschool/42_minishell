/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:14:25 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 13:37:59 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_parse_split(t_parser *prs)
{
	if ((prs->str && prs->str[0]) || prs->spase == 1)
		prs->mass = ft_add_line(prs->mass, prs->str);
	free(prs->str);
	prs->str = NULL;
}

void	parse_spase(char *str, t_parser *prs, int i)
{
	if (prs->red == '>' || prs->red == '<')
		prs->str = ft_charjoin(prs->str, str[i]);
	else
		ft_parse_split(prs);
	prs->spase = 0;
}

void	parse_char(char *str, t_parser *prs, int i)
{
	prs->str = ft_charjoin(prs->str, str[i]);
	prs->red = 0;
}

char	*parce(char *str, t_parser *prs, int i)
{
	prs->str = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			str = ft_gap(str, &i, prs);
		else if (str[i] == '\\')
			str = ft_slash(str, &i, prs);
		else if (str[i] == '\"')
			str = ft_quotechar(str, &i, prs);
		else if (str[i] == '$')
			str = ft_dollar(str, &i, prs);
		else if (ft_strchr("><|&*;()", str[i]))
			str = ft_replace(str, &i, str[i], prs);
		else if (ft_strchr(" \t><", str[i]))
			parse_spase(str, prs, i);
		else
			parse_char(str, prs, i);
		if (i < 0)
			i = 0;
		else if (str[i] != '\0')
			i++;
	}
	ft_parse_split(prs);
	return (str);
}

char	**split_str(char *str, char **env)
{
	t_parser	*prs;
	char		**ret;

	prs = malloc(sizeof(t_parser));
	prs->quo = 0;
	prs->red = 0;
	prs->d_quo = 0;
	prs->r = 0;
	prs->spase = 0;
	prs->mass = NULL;
	if (!env)
		;
	str = parce(str, prs, 0);
	free(str);
	free(prs->str);
	ret = prs->mass;
	free (prs);
	return (ret);
}

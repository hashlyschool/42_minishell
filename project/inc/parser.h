/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:46:12 by a79856            #+#    #+#             */
/*   Updated: 2022/03/13 19:57:11 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_parser
{
	char	*str;
	char	**mass;
	int		quo;
	char	red;
}	t_parser;

char	*ft_gap(char *str, int *i, t_parser *prs);
char	*ft_slash(char *str, int *i, t_parser *prs);
char	*ft_quotechar(char *str, int *i, t_parser *prs);
char	*ft_dollar(char *str, int *i, char *start, char *end, t_parser *prs);
char	*ft_replace(char *str, int *i, char c, t_parser *prs);
char	*ft_charjoin(char *str, char c);
void	ft_parse_split(t_parser *prs);

#endif

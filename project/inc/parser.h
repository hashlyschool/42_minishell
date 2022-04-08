/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:46:12 by a79856            #+#    #+#             */
/*   Updated: 2022/04/08 22:06:17 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SYN_ERR "minishell: syntax error near unexpected token "

typedef struct s_parser
{
	char	*str;
	char	**mass;
	int		quo;
	char	red;
	int		d_quo;
	int		r;
	int		spase;
}	t_parser;

typedef struct s_dollar
{
	int		plus;
	int		flag;
	int		index;
	int		end;
}	t_dollar;

char	*ft_gap(char *str, int *i, t_parser *prs);
char	*ft_slash(char *str, int *i, t_parser *prs);
char	*ft_quotechar(char *str, int *i, t_parser *prs);
char	*ft_dollar(char *str, int *i, t_parser *prs);
char	*ft_replace(char *str, int *i, char c, t_parser *prs);
char	*ft_charjoin(char *str, char c);
void	ft_parse_split(t_parser *prs);
char	**ft_minishell_split(char const *s);

#endif

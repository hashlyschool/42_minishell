/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:46:12 by a79856            #+#    #+#             */
/*   Updated: 2022/04/27 12:17:23 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SYN_ERR "minishell: syntax error near unexpected token `"
# define TOK_ERR "syntax error near unexpected token `newline`\n"
# define END_ERR "syntax error: unexpected end of file\n"

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

	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;
}	t_dollar;

typedef struct main
{
	char	**m;
	char	*str1;
	char	*str2;
	char	*new_str;
	char	*new_str2;
	int		len;
}	t_main;

typedef struct s_lex_q
{
	char	*error;
	int		w;
	int		i;
	int		red;
	char	q;
	char	c;
	int		count_char;
	int		ops;
	int		spase;
}	t_lex_q;

typedef struct s_preparse
{
	char	c;
	int		i;
	int		c2;
	int		c3;
	int		let;
	int		j;
}	t_preparse;

typedef struct t_replase
{
	int			j;
	int			flag;
	char		*tmp;
	char		c;
	t_parser	*p;
}	t_replase;

typedef struct t_replase_utills
{
	char	*tmp;
	int		j;
	char	*str2;
	int		len;
	int		len_prs;
}	t_rep_utils;

typedef struct s_check_red
{
	int		i;
	int		red;
	char	q;
	int		start;
	int		finish;
}	t_red;

typedef struct s_parsing
{
	char	*str;
	char	**ret;
	char	*error;
}	t_parsing;

char	*ft_gap(char *str, int *i, t_parser *prs);
char	*ft_slash(char *str, int *i, t_parser *prs);
char	*ft_quotechar(char *str, int *i, t_parser *prs);
char	*ft_dollar(char *str, int *i, t_parser *prs);
char	*ft_replace(char *str, int *i, char c, t_parser *prs);
char	*ft_charjoin(char *str, char c);
void	ft_parse_split(t_parser *prs);
char	**ft_minishell_split(char const *s);
char	*ft_queote_dollar(char *str, char *new_str, int i);
char	*ft_charjoin_no_free(char *str, char c);
char	*ft_replace_util(char *str, int *i, char *start, t_replase *t);
int		ft_is_fd(char *str, int i);
char	**parsing(char ***env, char *cmd, char mode_work);
char	**split_str(char *str, char **env);
char	*get_line(char ***env);

//lexer//
char	*lexer_init(char *str);
char	preparse_init(char *str);
char	*init_check_red(char *str);
char	*lexer(char *str, t_lex_q *data);
void	lexer_true(char *str, t_lex_q *data);

#endif

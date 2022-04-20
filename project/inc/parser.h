/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:46:12 by a79856            #+#    #+#             */
/*   Updated: 2022/04/20 02:28:30 by a79856           ###   ########.fr       */
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

//lexer//

// typedef enum e_type
// {
// 	CMD,
// 	ARG,
// 	REDIR_IN,
// 	REDIR_OUT,
// 	REDIR_APPEND,
// 	REDIR_FILE,
// 	PIPE,
// 	SEP
// }				t_type;

// typedef struct s_token
// {
// 	char		*str;
// 	int			len;
// 	int			screened;
// 	t_type		type;

// 	void		(*append)(struct s_token *self, char *to_append);
// 	void		(*remove)(struct s_token *self, size_t i);
// 	void		(*prepare)(struct s_token *self, int exit_status);
// 	void		(*del)(struct s_token	*self);
// }				t_token;

// typedef struct s_lexer
// {
// 	char	*string;
// 	char	*buf;
// 	t_token	**tokens;
// 	size_t	tokens_len;

// 	void	(*del)(struct s_lexer	*self);
// 	int		(*tokenize)(struct s_lexer	*self);
// 	int		(*check_grammar)(struct s_lexer	*self);
// }				t_lexer;

///////

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

#endif

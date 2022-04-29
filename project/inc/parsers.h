/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 01:59:08 by a79856            #+#    #+#             */
/*   Updated: 2022/04/28 17:09:39 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERS_H
# define PARSERS_H

typedef enum e_type
{
	CMD,
	ARG,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_FILE,
	REDIR_HEREDOC,
	PIPES,
	SEP,
	AMPER,
}				t_type;

typedef struct s_token
{
	char		*str;
	int			len;
	int			screened;
	t_type		type;
	char		q;

	void		(*append)(struct s_token *self, char *to_append);
	void		(*remove)(struct s_token *self, size_t i);
	void		(*prepare)(struct s_token *self, int exit_status);
	void		(*del)(struct s_token *self);
}				t_token;

typedef struct s_lexer
{
	char	*string;
	char	*buf;
	t_token	**tokens;
	size_t	tokens_len;

	void	(*del)(struct s_lexer	*self);
	int		(*tokenize)(struct s_lexer	*self);
	int		(*check_grammar)(struct s_lexer	*self);
}				t_lexer;

typedef struct s_job
{
	char	*cmd;
	char	**argv;
	size_t	argc;
	t_list	*redir_in;
	t_list	*redir_out;
	t_list	*redir_append;
	void	(*del)(struct s_job	*self);
}				t_job;

typedef struct s_parsers
{
	char	*string;
	t_lexer	*lexer;
	t_job	**jobs;
	size_t	jobs_len;
	size_t	pos;
	int		exit_status;

	void	(*del)(struct s_parsers	*self);
}				t_parsers;

void	parser_init(t_parsers *self, char *string_to_parse, int exit_status);
void	parser_del(t_parsers *self);
int		parser_next(t_parsers *self);
void	parser_refresh(t_parsers *self, int exit_status);

int		parser_make_jobs(t_parsers *self);
t_job	*job_new(void);
void	job_append_arg(t_job *self, char *arg);

t_lexer	*lexer_new(char *string);
void	lexer_del(t_lexer *self);

int		lexer_tokenize(t_lexer *self);
void	lexer_append_token(t_lexer *self, t_token *token);
void	lexer_token_type(t_lexer *self, t_token *token);
t_token	*lexer_get_token(t_lexer *self);
void	lexer_quotes_expandvar(t_lexer *self);
void	lexer_expandvar(t_lexer *self);
void	lexer_insert_varvalue(t_lexer *self, char *var_value);
char	*lexer_get_varname(t_lexer *self);

t_token	*token_new(void);
void	token_del(t_token *self);
void	token_append(t_token *self, char *src);
void	token_prepare(t_token *self, int exit_status);

int		is_quotes(char c);
int		is_tokensep(char c);

void	lexer_quotes(t_token *token, char **p_token_end);

int		lexer_check_grammar(t_lexer *self);

//error
void	process_syserror(void);
void	process_error(void);
int		process_input_error(size_t errcode);
int		perr(char *cmd, char *arg, char *err, int code);
int		ft_strcmp(const char *s1, const char *s2);

char	*lexer_check_2(char	*token_end, t_token *token);
#endif

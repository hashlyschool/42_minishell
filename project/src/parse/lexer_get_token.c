/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:49:40 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 12:36:08 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	lexer_check_sep(t_lexer *self, t_token *token, char **p_token_end)
{
	char	*token_end;

	token_end = *p_token_end;
	if (is_tokensep(*token_end) && is_tokensep(*self->buf))
	{
		token->append(token, token_end);
		if (*token_end == '>')
		{
			if ((*token_end + 1) && ((*(token_end + 1)) == '>'))
			{
				token_end++;
				token_append(token, token_end);
			}
			else if ((*token_end + 1) && ((*token_end + 1) == '<'))
				return (process_input_error(2));
		}
		else
		{
			if ((*token_end + 1) && ((*(token_end + 1)) == '<'))
				token_end = lexer_check_2(token_end, token);
		}
		token_end++;
	}
	*p_token_end = token_end;
	return (0);
}

static void	lexer_check_space(t_lexer *self, char *token_end)
{
	if (*token_end == ' ')
		self->buf = token_end + 1;
	else
		self->buf = token_end;
}

static int	quotes_error(t_token *token, char *token_end)
{
	int	error;

	error = 0;
	if (!*token_end)
	{	
		if (token->q == '\'')
			error = 1;
		else if (token->q == '\"')
			error = 3;
		token->del(token);
		return (process_input_error(error));
	}
	return (0);
}

static int	lexer_form_token(t_token *token, char **p_token_end)
{
	char	*token_end;

	token_end = *p_token_end;
	if (*token_end == '\\')
	{
		token->append(token, token_end);
		token_end++;
		token->append(token, token_end);
		token->screened = 1;
	}
	else if (is_quotes(*token_end))
	{
		lexer_quotes(token, &token_end);
		if (quotes_error(token, token_end))
			return (-1);
	}
	else
		token->append(token, token_end);
	token_end++;
	*p_token_end = token_end;
	return (0);
}

t_token	*lexer_get_token(t_lexer *self)
{
	t_token	*token;
	char	*token_end;

	token = token_new();
	token_end = self->buf;
	while (*token_end && *token_end != ' ' && !is_tokensep(*token_end))
	{
		if (lexer_form_token(token, &token_end) == -1)
			return (NULL);
	}
	if (lexer_check_sep(self, token, &token_end) == -1)
		return (NULL);
	lexer_check_space(self, token_end);
	return (token);
}

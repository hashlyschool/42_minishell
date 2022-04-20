/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:39:36 by gcredibl          #+#    #+#             */
/*   Updated: 2022/04/20 03:11:24 by a79856           ###   ########.fr       */
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
	if (!*token_end)
	{
		token->del(token);
		return (process_input_error(1));
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

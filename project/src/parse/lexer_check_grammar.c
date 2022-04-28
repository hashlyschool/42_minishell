/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_grammar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:49:35 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 02:27:04 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	lexer_check_sep(t_lexer *self, size_t i)
{
	t_token	*token_prev;

	if (i == 0)
		return (-1);
	token_prev = self->tokens[i - 1];
	if ((token_prev->type == PIPES)
		|| (token_prev->type == SEP)
		|| (token_prev->type == REDIR_IN)
		|| (token_prev->type == REDIR_OUT)
		|| (token_prev->type == REDIR_APPEND)
		|| (token_prev->type == REDIR_HEREDOC)
		|| (token_prev->type == AMPER))
		return (-1);
	return (0);
}

int	lexer_check_redir(t_lexer *self, size_t i)
{
	t_token	*token_prev;

	if (i == self->tokens_len - 1)
		return (-1);
	if (i > 0)
	{
		token_prev = self->tokens[i - 1];
		if (token_prev->type == REDIR_IN
			|| token_prev->type == REDIR_OUT
			|| token_prev->type == REDIR_APPEND
			|| token_prev->type == REDIR_HEREDOC)
			return (-1);
	}
	return (0);
}

int	lexer_check_grammar(t_lexer *self)
{
	t_token	*token_cur;
	size_t	i;

	i = 0;
	while (i < self->tokens_len)
	{
		token_cur = self->tokens[i];
		if ((token_cur->type == REDIR_IN) && (lexer_check_redir(self, i) == -1))
			return (process_input_error(2));
		else if ((token_cur->type == REDIR_OUT)
			&& (lexer_check_redir(self, i) == -1))
			return (process_input_error(4));
		else if ((token_cur->type == REDIR_HEREDOC)
			&& (lexer_check_redir(self, i) == -1))
			return (process_input_error(5));
		else if ((token_cur->type == REDIR_APPEND)
			&& (lexer_check_redir(self, i) == -1))
			return (process_input_error(6));
		i++;
	}
	return (0);
}

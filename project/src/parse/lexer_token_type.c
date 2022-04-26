/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:49:50 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/26 23:28:00 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	lexer_previous_type(t_lexer *self, t_token *token)
{
	size_t	len;

	len = self->tokens_len;
	if (len == 0)
		token->type = CMD;
	else if ((self->tokens[len - 1])->type == CMD
		|| (self->tokens[len - 1])->type == ARG)
		token->type = ARG;
	else if ((self->tokens[len - 1])->type == REDIR_OUT
		|| (self->tokens[len - 1])->type == REDIR_IN
		|| (self->tokens[len - 1])->type == REDIR_APPEND
		|| (self->tokens[len - 1])->type == REDIR_HEREDOC)
		token->type = REDIR_FILE;
	else if ((self->tokens[len - 1])->type == PIPES
		|| (self->tokens[len - 1])->type == SEP
		|| (self->tokens[len - 1])->type == AMPER)
		token->type = CMD;
	else
		token->type = CMD;
}

void	lexer_token_type(t_lexer *self, t_token *token)
{
	char	*token_str;

	token_str = token->str;
	if (!ft_strcmp(token_str, "|"))
		token->type = PIPES;
	else if (!ft_strcmp(token_str, "&"))
		token->type = AMPER;
	else if (!ft_strcmp(token_str, ";"))
		token->type = SEP;
	else if (!ft_strcmp(token_str, "<<"))
		token->type = REDIR_HEREDOC;
	else if (!ft_strcmp(token_str, ">>"))
		token->type = REDIR_APPEND;
	else if (!ft_strcmp(token_str, ">"))
		token->type = REDIR_OUT;
	else if (!ft_strcmp(token_str, "<"))
		token->type = REDIR_IN;
	else
		lexer_previous_type(self, token);
}

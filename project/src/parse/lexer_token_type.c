/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:39:45 by gcredibl          #+#    #+#             */
/*   Updated: 2022/04/20 03:11:29 by a79856           ###   ########.fr       */
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
		|| (self->tokens[len - 1])->type == REDIR_APPEND)
		token->type = REDIR_FILE;
	else if ((self->tokens[len - 1])->type == PIPES
		|| (self->tokens[len - 1])->type == SEP)
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
	else if (!ft_strcmp(token_str, ";"))
		token->type = SEP;
	else if (!ft_strcmp(token_str, ">"))
		token->type = REDIR_OUT;
	else if (!ft_strcmp(token_str, ">>"))
		token->type = REDIR_APPEND;
	else if (!ft_strcmp(token_str, "<"))
		token->type = REDIR_IN;
	else
		lexer_previous_type(self, token);
}

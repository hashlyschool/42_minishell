/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:49:46 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 12:36:03 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*lexer_check_2(char	*token_end, t_token *token)
{
	token_end++;
	token_append(token, token_end);
	return (token_end);
}

void	lexer_quotes(t_token *token, char **p_token_end)
{
	char	*token_end;

	token_end = *p_token_end;
	token->append(token, token_end);
	if (*token_end++ == '\'')
	{
		while (*token_end && *token_end != '\'')
			token->append(token, token_end++);
		token->q = '\'';
	}
	else
	{
		while (*token_end && *token_end != '\"')
		{
			if (*token_end == '\\')
				token->append(token, token_end++);
			token->append(token, token_end++);
		}
		token->q = '"';
	}
	if (*token_end)
		token->append(token, token_end);
	*p_token_end = token_end;
}

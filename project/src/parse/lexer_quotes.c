/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:39:41 by gcredibl          #+#    #+#             */
/*   Updated: 2022/04/20 03:11:26 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 
#include "../../inc/minishell.h"

void	lexer_quotes(t_token *token, char **p_token_end)
{
	char	*token_end;

	token_end = *p_token_end;
	token->append(token, token_end);
	if (*token_end++ == '\'')
	{
		while (*token_end && *token_end != '\'')
			token->append(token, token_end++);
	}
	else
	{
		while (*token_end && *token_end != '\"')
		{
			if (*token_end == '\\')
				token->append(token, token_end++);
			token->append(token, token_end++);
		}
	}
	if (*token_end)
		token->append(token, token_end);
	*p_token_end = token_end;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:49:54 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/26 23:02:30 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	lexer_append_token(t_lexer *self, t_token *token)
{
	t_token	**tmp;
	size_t	i;

	i = 0;
	tmp = (t_token **)malloc(sizeof(t_token *) * (self->tokens_len + 2));
	if (!tmp)
		process_syserror();
	if (self->tokens_len == 0)
	{
		tmp[0] = token;
		tmp[1] = NULL;
	}
	else
	{
		while (self->tokens[i])
		{
			tmp[i] = self->tokens[i];
			i++;
		}
		tmp[i] = token;
		tmp[++i] = NULL;
		free(self->tokens);
	}
	self->tokens = tmp;
	self->tokens_len += 1;
}

int	lexer_tokenize(t_lexer *self)
{
	t_token		*token;

	while (*self->buf)
	{
		while (*self->buf == ' ')
			self->buf++;
		token = lexer_get_token(self);
		if (token == NULL)
			return (-1);
		if (token->str)
		{
			lexer_token_type(self, token);
			lexer_append_token(self, token);
		}
		else
			token->del(token);
	}
	return (0);
}

void	lexer_del(t_lexer *self)
{
	int		i;

	i = 0;
	if (self)
	{
		if (self->string)
		{
			free(self->string);
			self->string = NULL;
		}
		if (self->tokens)
		{
			while (self->tokens[i])
			{
				self->tokens[i]->del(self->tokens[i]);
				i++;
			}
			free(self->tokens);
			self->tokens = NULL;
		}
		free(self);
		self = NULL;
	}
}

t_lexer	*lexer_new(char *string)
{
	t_lexer	*self;

	self = (t_lexer *)malloc(sizeof(t_lexer));
	if (!self)
		process_syserror();
	self->string = ft_strdup(string);
	self->buf = self->string;
	self->del = lexer_del;
	self->tokens = NULL;
	self->tokens_len = 0;
	self->tokenize = lexer_tokenize;
	self->check_grammar = lexer_check_grammar;
	return (self);
}

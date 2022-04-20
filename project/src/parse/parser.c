/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:39:59 by gcredibl          #+#    #+#             */
/*   Updated: 2022/04/20 03:11:36 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 
#include "../../inc/minishell.h"

void	parser_del(t_parsers *self)
{
	size_t	i;

	i = 0;
	if (self)
	{
		free(self->string);
		self->string = NULL;
		if (self->lexer)
		{
			self->lexer->del(self->lexer);
			self->lexer = NULL;
		}
		if (self->jobs)
		{
			while (self->jobs[i])
			{
				(self->jobs[i])->del(self->jobs[i]);
				self->jobs[i] = NULL;
				i++;
			}
			self->jobs = NULL;
		}
	}
}

void	parser_refresh(t_parsers *self, int exit_status)
{
	size_t	i;

	i = 0;
	if (self)
	{
		if (self->jobs)
		{
			while (i < self->jobs_len)
			{
				(self->jobs[i])->del(self->jobs[i]);
				self->jobs[i] = NULL;
				i++;
			}
			free(self->jobs);
			self->jobs = NULL;
			self->jobs_len = 0;
		}
		self->exit_status = exit_status;
	}
}

void	parser_init(t_parsers *self, char *string_to_parse, int exit_status)
{
	self->string = string_to_parse;
	self->exit_status = exit_status;
	self->lexer = NULL;
	self->jobs = NULL;
	self->jobs_len = 0;
	self->pos = 0;
	self->del = parser_del;
}

int	parser_next(t_parsers *self)
{
	if (!self->lexer)
	{
		self->lexer = lexer_new(self->string);
		if ((self->lexer->tokenize(self->lexer) == -1)
			|| self->lexer->check_grammar(self->lexer) == -1)
		{
			self->lexer->del(self->lexer);
			return (0);
		}
	}
	if (self->pos < self->lexer->tokens_len)
	{
		parser_make_jobs(self);
		return (1);
	}
	else
	{
		self->lexer->del(self->lexer);
		return (0);
	}
}

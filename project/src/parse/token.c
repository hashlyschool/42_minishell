/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:50:14 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 03:24:13 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	token_append(t_token *self, char *src)
{
	char			*tmp;
	char			*string;

	string = self->str;
	tmp = (char *)malloc((self->len + 2) * sizeof(char));
	if (!tmp)
		process_syserror();
	if (!string)
	{
		ft_strlcpy(tmp, src, 2);
		self->len = 1;
	}
	else
	{
		ft_strlcpy(tmp, string, self->len + 1);
		ft_strlcat(tmp, src, self->len + 2);
		self->len += 1;
		free(string);
	}
	self->str = tmp;
}

void	token_remove(t_token *self, size_t i)
{
	char			*tmp;
	char			*string;
	char			*to_join;

	string = self->str;
	if (string)
	{
		string[i] = '\0';
		to_join = string + i + 1;
		tmp = ft_strjoin(string, to_join);
		if (!tmp)
			process_syserror();
		free(string);
		self->len -= 1;
		self->str = tmp;
	}
}

void	token_join(t_token *self, char *src)
{
	char			*tmp;
	char			*string;

	string = self->str;
	tmp = ft_strjoin(string, src);
	if (!tmp)
		process_syserror();
	if (string)
		free(string);
	self->len = ft_strlen(tmp);
	self->str = tmp;
}

void	token_del(t_token *self)
{
	if (self)
	{
		if (self->str)
		{
			free(self->str);
			self->str = NULL;
		}
		free(self);
		self = NULL;
	}
}

t_token	*token_new(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		process_syserror();
	token->str = NULL;
	token->len = 0;
	token->screened = 0;
	token->type = 0;
	token->append = token_append;
	token->remove = token_remove;
	token->prepare = token_prepare;
	token->del = token_del;
	return (token);
}

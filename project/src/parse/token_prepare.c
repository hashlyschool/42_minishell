/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_prepare.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 17:40:12 by a79856            #+#    #+#             */
/*   Updated: 2022/04/27 13:10:31 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*token_get_varname(t_token *self, size_t i)
{
	char		*string;
	char		*varname;
	char		tmp;

	varname = NULL;
	if (self->str[i + 1])
	{
		string = self->str + i + 1;
		if (ft_isdigit(*string) || *string == '?')
			string++;
		else
		{
			while (ft_isalnum(*string) || *string == '_')
				string++;
		}
		tmp = *string;
		*string = '\0';
		varname = ft_strdup(self->str + i + 1);
		if (!varname)
			process_syserror();
		*string = tmp;
	}
	return (varname);
}

static void	token_insert_varvalue(t_token *self, size_t *index, char *varvalue,
		char *varname)
{
	char		*tmp1;
	char		*tmp2;
	size_t		i;

	i = *index;
	self->str[i] = '\0';
	i++;
	tmp1 = ft_strjoin(self->str, varvalue);
	if (!tmp1)
		process_syserror();
	i += ft_strlen(varname);
	tmp2 = ft_strjoin(tmp1, self->str + i);
	if (!tmp2)
		process_syserror();
	free(tmp1);
	free(self->str);
	self->str = tmp2;
	self->len = ft_strlen(tmp2);
}

static void	token_expandvar(t_token *self, size_t *i, int exit_status)
{
	char		*varname;
	char		*varvalue;

	varname = token_get_varname(self, *i);
	if (ft_isdigit(*varname))
	{
		if (!ft_strcmp(varname, "0"))
			varvalue = ft_strdup("minihell");
		else
			varvalue = ft_strdup("");
	}
	else if (!ft_strcmp(varname, "?"))
		varvalue = ft_itoa(exit_status);
	else
		varvalue = ft_strdup(varname);
	if (!varvalue)
		process_syserror();
	token_insert_varvalue(self, i, varvalue, varname);
	free(varname);
	*i += ft_strlen(varvalue);
	free(varvalue);
}

static void	token_handle_dquotes(t_token *self, size_t *index, int exit_status)
{
	size_t		i;

	exit_status = 0;
	i = (*index);
	self->remove(self, i);
	while (self->str[i] != '\"')
	{
		if ((self->str[i] == '\\')
			&& (self->str[i + 1] == '\\'
				|| self->str[i + 1] == '$'
				|| self->str[i + 1] == '\"'))
		{
			self->remove(self, i);
			i++;
		}
		else
			i++;
	}
	self->remove(self, i);
	(*index) = i;
}

void	token_prepare(t_token *self, int exit_status)
{
	size_t		i;

	i = 0;
	while (self->str[i])
	{
		if (self->str[i] == '\\')
			self->remove(self, i++);
		else if (self->str[i] == '$' && self->str[i + 1]
			&& (ft_isalnum(self->str[i + 1]) || self->str[i + 1] == '_'
				|| self->str[i + 1] == '?' || is_quotes(self->str[i + 1])))
			token_expandvar(self, &i, exit_status);
		else if (self->str[i] == '\'')
		{
			self->remove(self, i);
			while (self->str[i] != '\'')
				i++;
			self->remove(self, i);
		}
		else if (self->str[i] == '\"')
			token_handle_dquotes(self, &i, exit_status);
		else
			i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/04/27 17:47:48 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**parsing_error(char ***env, char *str)
{
	char		*help;

	help = ft_charjoin_no_free(SYN_ERR, preparse_init(str));
	free(str);
	ft_set_ret(2, ft_strjoin_free_s1(help, "'\n"), *env);
	return (NULL);
}

char	**parsing_error_2(char ***env, char *str, char *error)
{
	free(str);
	ft_set_ret(2, error, *env);
	free(error);
	return (NULL);
}

char	**parsing_error_3(char ***env, char *str)
{
	free(str);
	ft_set_ret(2, "", *env);
	return (NULL);
}

void	parsing_error_4(t_parsing	*p)
{
	p->ret = ft_add_line(p->ret, p->str);
	free(p->str);
}

char	**parsing(char ***env, char *cmd, char mode_work)
{
	t_parsing	p;
	t_parsers	prs;

	p.error = NULL;
	p.ret = NULL;
	if (mode_work)
		p.str = ft_substr(cmd, 0, ft_strlen(cmd) - 1);
	else
		p.str = get_line(env);
	parser_init(&prs, p.str, 0);
	if (!(parser_next(&prs)))
		return (parsing_error_3(env, p.str));
	if (preparse_init(p.str) != 0)
		return (parsing_error(env, p.str));
	p.error = lexer_init(p.str);
	if (p.error != NULL)
		return (parsing_error_2(env, p.str, p.error));
	free(p.error);
	if (p.str == NULL)
		parsing_error_4(&p);
	else
		p.ret = split_str(p.str, *env);
	return (p.ret);
}

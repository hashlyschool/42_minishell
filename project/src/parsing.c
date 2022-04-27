/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/04/27 02:39:55 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_line(char ***env)
{
	char	*line_read;
	char	*promt;

	promt = get_promt(*env);
	line_read = readline(promt);
	free(promt);
	if (line_read && *line_read)
		add_history(line_read);
	if (!line_read)
	{
		ft_free_envp(&env);
		sig_d(0);
	}
	return (line_read);
}

void	ft_parse_split(t_parser *prs)
{
	if ((prs->str && prs->str[0]) || prs->spase == 1)
		prs->mass = ft_add_line(prs->mass, prs->str);
	free(prs->str);
	prs->str = NULL;
}

void	parse_spase(char *str, t_parser *prs, int i)
{
	if (prs->red == '>' || prs->red == '<')
		prs->str = ft_charjoin(prs->str, str[i]);
	else
		ft_parse_split(prs);
	prs->spase = 0;
}

void	parse_char(char *str, t_parser *prs, int i)
{
	prs->str = ft_charjoin(prs->str, str[i]);
	prs->red = 0;
}

char	*parce(char *str, t_parser *prs)
{
	int	i;

	i = 0;
	prs->str = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			str = ft_gap(str, &i, prs);
		else if (str[i] == '\\')
			str = ft_slash(str, &i, prs);
		else if (str[i] == '\"')
			str = ft_quotechar(str, &i, prs);
		else if (str[i] == '$')
			str = ft_dollar(str, &i, prs);
		else if (ft_strchr("><|&*;()", str[i]))
			str = ft_replace(str, &i, str[i], prs);
		else if (ft_strchr(" \t><", str[i]))
			parse_spase(str, prs, i);
		else
			parse_char(str, prs, i);
		if (str[i] != '\0' || (str[i] == '\0' && i < 0))
			i++;
	}
	ft_parse_split(prs);
	return (str);
}

static char	**split_str(char *str, char **env)
{
	t_parser	*prs;
	char		**ret;

	prs = malloc(sizeof(t_parser));
	prs->quo = 0;
	prs->red = 0;
	prs->d_quo = 0;
	prs->r = 0;
	prs->spase = 0;
	prs->mass = NULL;
	if (!env)
		;
	str = parce(str, prs);
	free(str);
	free(prs->str);
	ret = prs->mass;
	free (prs);
	return (ret);
}

// char	*check_redirect(char *str)
// {
// 	while (str[i] != '\0')
// 	{
// 		if (start > 0 && red > 0 && finish > 0)
// 		{
// 			red = 0;
// 			start = 0;
// 			finish = 0;
// 		}
// 		while (ft_strchr(">< \r\v\n\t", str[i]) != NULL
// 			&& q == '0' && str[i] != '\0')
// 		{
// 			if (ft_strchr("<>", str[i]))
// 				red++;
// 			i++;
// 		}
// 		if (str[i] == '\"' || str[i] == '\'')
// 		{
// 			if (str[i] == q)
// 				q = '0';
// 			else
// 				q = str[i];
// 		}
// 		if (str[i] == '\0')
// 			break ;
// 		if (red == 0)
// 			start++;
// 		else
// 			finish++;
// 		i++;
// 	}
// 	if (red > 0 && ((red == 0 && finish == 0) || finish == 0))
// 		return (TOK_ERR);
// 	return (NULL);
// }

char	*init_check_red(char *str)
{
	t_red	r;

	r.i = 0;
	r.red = 0;
	r.start = 0;
	r.finish = 0;
	r.q = '0';
	return (check_redirect(str, &r));
}

char	**parsing(char ***env, char *cmd ,char mode_work)
{
	char		*str;
	char		**ret;
	char		*error;
	char		*help;
	t_parsers	prs;

	error = NULL;
	ret = NULL;
	if (mode_work)
		str = ft_substr(cmd, 0, ft_strlen(cmd) - 1);
	else
		str = get_line(env);
	parser_init(&prs, str, 0);
	if (!(parser_next(&prs)))
	{
		free(str);
		ft_set_ret(2, "", *env);
		return (NULL);
	}
	if (preparse_init(str) != 0)
	{
		help = ft_charjoin_no_free(SYN_ERR, preparse_init(str));
		free(str);
		ft_set_ret(2, ft_strjoin_free_s1(help, "'\n"), *env);
		return (NULL);
	}
	error = lexer_init(str);
	if (error != NULL)
	{
		free(str);
		ft_set_ret(2, error, *env);
		free(error);
		return (NULL);
	}
	free(error);
	if (str == NULL)
	{
		ret = ft_add_line(ret, str);
		free(str);
	}
	else
		ret = split_str(str, *env);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/04/26 21:51:33 by sstyx            ###   ########.fr       */
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
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|'
			|| str[i] == '&' || str[i] == '*' || str[i] == ';' || str[i] == '('
			|| str[i] == ')')
			str = ft_replace(str, &i, str[i], prs);
		else if (str[i] == ' ' || str[i] == '\t' || str[i] == '>' || str[i] == '<')
		{
			parse_spase(str, prs, i);
			// if (prs->red == '>' || prs->red == '<')
			// 	prs->str = ft_charjoin(prs->str, str[i]);
			// else
			// 	ft_parse_split(prs);
			// prs->spase = 0;
		}
		else
		{
			prs->str = ft_charjoin(prs->str, str[i]);
			prs->red = 0;
		}
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

/* функция для посчета кавычек */
char	preparse(char *str)
{
	char	c;
	int		i;
	int		c2;
	int		c3;
	int		dollar;
	int		let;
	int		j;

	i = 0;
	c = '0';
	c2 = 0;
	c3 = 0;
	j = 0;
	let	= 0;
	dollar = 0;
	while (str[i])
	{
		if ((str[i] == '\'') || str[i] == '"' || str[i] == '\\')
		{
			if (!(i != 0 && str[i - 1] == '\\' && j != 1) && str[i] != '\\')
			{
				if (c == str[i])
					c = '0';
				else if (c == '0')
					c = str[i];
				j = 0;
			}
			else if (i != 0 && str[i - 1] == '\\' && str[i] == '\\')
				j = 1;
		}
		else if (str[i] == '{' || str[i] == '}')
		{
			if (str[i] == '{' && c != '\'' && c != '\"')
				c3++;
			else if (str[i] == '}' && c != '\'' && c != '\"')
				c3--;
			c = str[i];
		}
		else if (str[i] == '(' || str[i] == ')')
		{
			if (str[i] == '(' && c != '\'' && c != '\"')
			{
				c2++;
				let = 0;
			}
			else if (str[i] == ')' && (c != '\'' && c != '\"') && ((let > 0 && c2 > 0) || c2 == 0))
				c2--;
			c = str[i];
		}
		else if ((ft_strchr(" \r\v\n\t", str[i])) == NULL)
			let++;
		i++;
	}
	if (c3 != 0 || c2 != 0)
		return (c);
	return (0);
}

char	*lexer(char *str, t_lex_q *data)
{
	while (str[data->i] != '\0')
	{
		data->c = 0;
		data->count_char = 0;
		data->ops = 0;
		while (ft_strchr(";& \r\v\n\t|<>", str[data->i]) != NULL && data->q == '0' && str[data->i] != '\0')
		{
			if (ft_strchr(";&|", str[data->i]))
			{
				if (data->red == 0 || data->count_char > 1 || (data->count_char == 1 && data->c == ';') ||
				(data->spase == 1 && data->count_char == 1))
				{
					if (((data->error != NULL && data->error[1] == str[data->i])
					|| !(data->error)) && ft_strlen(data->error) != 2)
					{
						if (str[data->i] == ';' && data->ops == 1 && data->red == 0)
							;
						else 
						{
							if (data->c == ';' && data->count_char == 1 && str[data->i] == ';' && data->ops != 1)
								data->error = ft_charjoin(data->error, str[data->i]);
							data->error = ft_charjoin(data->error, str[data->i]);
						}
					}
				}
				else
				{
					data->c = str[data->i];
					if (data->error)
						free(data->error);
					data->error = NULL;
					data->spase= 0;
				}
				data->count_char++;
			}
			else
			{
				if (data->c == ';' || (data->error != NULL && data->error[0] == ';'))
					data->ops = 1;
				data->spase = 1;
			}
			data->i++;
			data->w = 1;
		}
		if (data->c != 0)
			data->red = 0;
		if (str[data->i] == '\"' || str[data->i] == '\'')
		{
			if (str[data->i] == data->q)
				data->q = '0';
			else
				data->q = str[data->i];
		}
		else if (str[data->i] != '\0')
			data->red++;
		if (data->w == 1)
		{
			data->i--;
			data->w = 0;
		}
		data->i++;
	}
	if ((data->error != NULL && str[data->i] == '\0'))
		return (ft_strjoin_free_s2(SYN_ERR, ft_strjoin_free_s1(data->error, "\'\n")));
	if ((data->c != ';' && data->c != 0 && data->red != 1))
		return (END_ERR);
	return (NULL);
}

char	*lexer_init(char *str)
{
	t_lex_q data;

	data.i = 0;
	data.error = NULL;
	data.red = 0;
	data.q = '0';
	data.w = 0;
	data.ops = 0;
	data.count_char = 0;
	data.spase = 0;
	return(lexer(str, &data));
}

char	*check_redirect(char *str)
{
	int		i;
	int		red;
	char	q;
	int		start;
	int		finish;

	i = 0;
	red = 0;
	start = 0;
	finish = 0;
	q = '0';
	while (str[i] != '\0')
	{
		if (start > 0 && red > 0 && finish > 0)
		{
			red = 0;
			start = 0;
			finish = 0;
		}
		while (ft_strchr(">< \r\v\n\t", str[i]) != NULL && q == '0' && str[i] != '\0')
		{
			if (ft_strchr("<>", str[i]))
				red++;
			i++;
		}
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (str[i] == q)
				q = '0';
			else
				q = str[i];
		}
		if (str[i] == '\0')
			break ;
		if (red == 0)
			start++;
		else
			finish++;
		i++;
	}
	if (red > 0 && ((red == 0 && finish == 0) || finish == 0))
		return (TOK_ERR);
	return (NULL);
}

char	**parsing(char ***env, char *cmd ,char mode_work)
{
	char	*str;
	char	**ret;
	char	*error;
	t_parsers prs;

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
		ft_set_ret(2,"", *env);
		return (NULL);
	}
	if (preparse(str) != 0)
	{
		char *help = ft_charjoin_no_free(SYN_ERR, preparse(str));
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
	// else {
	// if (syntax_error(str, '|', 0, env) != -1 && syntax_error(str, ';', 0, env) != -1)
	// {
	// 	error = check_redirect(str);
	// 	if (error != NULL)
	// 	{
	// 		free(str);
	// 		ft_set_ret(2, error, *env);
	// 		return (NULL);
	// 	}
	// }
	if (str == NULL)
	{
		ret = ft_add_line(ret, str);
		free(str);
	}
	else
		ret = split_str(str, *env);
	return (ret);
}

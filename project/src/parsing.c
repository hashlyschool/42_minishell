/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/04/25 12:52:12 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// #include "parse/parsers.h"

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
			if (prs->red == '>' || prs->red == '<')
				prs->str = ft_charjoin(prs->str, str[i]);
			else
				ft_parse_split(prs);
			prs->spase = 0;
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

char	*lexer(char *str)
{
	char	*error;
	int		w;
	int		i;
	int		red;
	char	q;
	char	c;
	int		count_char;

	i = 0;
	error = NULL;
	red = 0;
	q = '0';
	w = 0;
	int ops = 0;
	count_char = 0;
	int spase = 0;
	while (str[i] != '\0')
	{
		c = 0;
		count_char = 0;
		ops = 0;
		while (ft_strchr(";& \r\v\n\t|<>", str[i]) != NULL && q == '0' && str[i] != '\0')
		{
			if (ft_strchr(";&|", str[i]))
			{
				if (red == 0 || count_char > 1 || (count_char == 1 && c == ';') ||
				(spase == 1 && count_char == 1))
				{
					if (((error != NULL && error[1] == str[i])
					|| !(error)) && ft_strlen(error) != 3)
					{
						if (str[i] == ';' && ops == 1 && red == 0)
							;
						else 
						{
							if (!(error))
								error = ft_charjoin(error, '`');
							if (c == ';' && count_char == 1 && str[i] == ';' && ops != 1)
								error = ft_charjoin(error, str[i]);
							error = ft_charjoin(error, str[i]);
						}
					}
				}
				else
				{
					c = str[i];
					if (error)
						free(error);
					error = NULL;
					spase= 0;
				}
				count_char++;
			}
			else
			{
				if (c == ';' || (error != NULL && error[1] == ';'))
					ops = 1;
				spase = 1;
			}
			i++;
			w = 1;
		}
		if (c != 0)
			red = 0;
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (str[i] == q)
				q = '0';
			else
				q = str[i];
		}
		else if (str[i] != '\0')
			red++;
		if (w == 1)
		{
			i--;
			w = 0;
		}
		i++;
	}
	if ((error != NULL && str[i] == '\0'))
		return (ft_strjoin_free_s2(SYN_ERR, ft_strjoin_free_s1(error, "\'\n")));
	if ((c != ';' && c != 0 && red != 1))
		return ("syntax error: unexpected end of file\n");
	return (NULL);
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
		return ("syntax error near unexpected token `newline`\n");
	return (NULL);
}

char	**parsing(char ***env, char *cmd ,char mode_work)
{
	char	*str;
	char	**ret;
	char	*error;
	t_parsers prs;

	ret = NULL;
	if (mode_work)
	//#ifdef __APPLE__
		str = ft_substr(cmd, 0, ft_strlen(cmd) - 1);//ft_strdup(cmd);
	//#else
		//str = ft_strdup(cmd);
	//#endif
	else
		str = get_line(env);
	//Здесь ошибочно считается ошибкой и кейс, вроде `)`
	//Вызывает вывод текста "minishell: syntax error: unexpected end of file"
	//А нужно выводить "bash: syntax error near unexpected token `)'"
	//
	//Еще ошибочно проверяется доллар (вернее он здесь не должен проверяться)
	//Если я все правильно понял в парсере, то здесь должны быть проверены
	//только кавычки
	//Хотя тебе лучше знать. может здесь стоит проверить и еще на какие-то ошибки парсера
	parser_init(&prs, str, 0);
	if (!(parser_next(&prs)))
	{
		free(str);
		ft_set_ret(2,"", *env);
		return (NULL);
	}
	if (preparse(str) != 0)
	{
		char *help = ft_charjoin_no_free("minishell: syntax error near unexpected token `", preparse(str));
		free(str);
		ft_set_ret(2, ft_strjoin_free_s1(help, "'\n"), *env);
		return (NULL);
	}
	error = lexer(str);
	if (error != NULL)
	{
		free(str);
		ft_set_ret(2, error, *env);
		return (NULL);
	}
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

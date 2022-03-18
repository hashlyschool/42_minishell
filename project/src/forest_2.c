/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forest_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:56:31 by hashly            #+#    #+#             */
/*   Updated: 2022/03/18 21:04:13 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	str_is_redirect(char *str)
{
	size_t	len;
	size_t	len_str;

	len_str = ft_strlen(str);
	len = ft_strlen(REDIR_RIGHT_ONE);
	if (len_str >= len + 2 && str[len] == ' ' && ft_isprint(str[len + 1]) && \
	ft_strncmp(str, REDIR_RIGHT_ONE, len) == 0)
		return (1);
	len = ft_strlen(REDIR_RIGHT_TWO);
	if (len_str >= len + 2 && str[len] == ' ' && ft_isprint(str[len + 1]) && \
	ft_strncmp(str, REDIR_RIGHT_TWO, len) == 0)
		return (2);
	len = ft_strlen(REDIR_LEFT_ONE);
	if (len_str >= len + 2 && str[len] == ' ' && ft_isprint(str[len + 1]) && \
	ft_strncmp(str, REDIR_LEFT_ONE, len) == 0)
		return (3);
	len = ft_strlen(REDIR_LEFT_TWO);
	if (len_str >= len + 2 && str[len] == ' ' && ft_isprint(str[len + 1]) && \
	ft_strncmp(str, REDIR_LEFT_TWO, len) == 0)
		return (4);
	return (0);
}

static void	ft_add_redir(t_node *node, char *str, char type)
{
	size_t	q_str;
	size_t	i;
	char	**ret;

	q_str = 0;
	while (node->data->redir && node->data->redir[q_str])
		q_str++;
	ret = (char **)malloc(sizeof(char *) * (q_str + 2));
	ret[q_str + 1] = NULL;
	i = -1;
	while (++i < q_str)
		ret[i] = node->data->redir[i];
	while (*str != ' ')
		str++;
	++str;
	if (type == 1)
		ret[q_str] = ft_strjoin("> ", str);
	if (type == 2)
		ret[q_str] = ft_strjoin(">> ", str);
	if (type == 3)
		ret[q_str] = ft_strjoin("< ", str);
	if (type == 4)
		ret[q_str] = ft_strjoin("<< ", str);
	free(node->data->redir);
	node->data->redir = ret;
}

void	ft_add_argv(t_node *node, char *str)
{
	int		q_str;
	char	**ret;

	q_str = 0;
	while (node->data->argv && node->data->argv[q_str])
		q_str++;
	ret = (char **)malloc(sizeof(char *) * (q_str + 2));
	ret[q_str + 1] = NULL;
	ret[q_str] = ft_strdup(str);
	while (--q_str >= 0)
		ret[q_str] = node->data->argv[q_str];
	if (node->data->argv)
		free(node->data->argv);
	node->data->argv = ret;
}

static void	fill_node(char *str, t_node *node)
{
	int	redir;

	node->exec = 0;
	redir = str_is_redirect(str);
	if (redir == 1)
		ft_add_redir(node, str, 1);
	else if (redir == 2)
		ft_add_redir(node, str, 2);
	else if (redir == 3)
		ft_add_redir(node, str, 3);
	else if (redir == 4)
		ft_add_redir(node, str, 4);
	else if (node->data->cmd == NULL)
		node->data->cmd = ft_strdup(str);
	else
		ft_add_argv(node, str);
}


/*
Здесь нужно проверить все токены, которые нам даны по сабжу
Т.е. 10 штук:
<	>	|	&&	(
<<	>>	;	||	)
Как проверять:
1) После < << > >> д.б. текст. Причем не обязательно через пробел
2) До ; должны быть команды
3) До и после | && || должны быть команды
4) Команда может быть в скобках или отдельно:
	cmd
	cmd argv...
	(cmd ...)

Может быть эту проверку легче будет сделать уже на свормированном дереве.
Я могу обьяснить как формируется дерево
*/
static char	check_error_in_cmd_line(char **line, t_node *node)
{
	char	error;

	error = 0;
	//check error
	//if error
	//	error = 1;
	if (line || node)
		;
	if (error)
	{
		ft_set_ret(2, "bash: syntax error near unexpected token `", node->env);
		ft_putstr_fd("token", 1); //need find token
		ft_putstr_fd("`'\n", 1);
	}
	return (error);
}

/*
Функция создания дерева по массиву строк, полученных из
парсинга входной строки.
Возвращает указатель на корень дерева.
*/
t_node	*get_forest(char **line, char **env)
{
	t_node	*root;
	t_node	*temp;
	int		i;

	temp = create_empty_node(env);
	root = temp;
	if (!line || check_error_in_cmd_line(line, root))
	{
		root->stop = 1;
		return (root);
	}
	i = -1;
	while (line && line[++i])
	{
		if (ft_strncmp(line[i], BR_LEFT, ft_strlen(BR_LEFT) + 1) == 0)
			temp = create_node_next_lvl(temp, env);
		else if (ft_strncmp(line[i], BR_RIGHT, ft_strlen(BR_RIGHT) + 1) == 0)
			temp = go_prev_lvl(temp);
		else if (ft_strncmp(line[i], AND_STR, ft_strlen(AND_STR) + 1) == 0)
			temp = create_next_node(temp, AND, env);
		else if (ft_strncmp(line[i], OR_STR, ft_strlen(OR_STR) + 1) == 0)
			temp = create_next_node(temp, OR, env);
		else if (ft_strncmp(line[i], PIPE_STR, ft_strlen(PIPE_STR) + 1) == 0)
			temp = create_next_node(temp, PIPE, env);
		else if (ft_strncmp(line[i], SEMICOLON, ft_strlen(SEMICOLON) + 1) == 0)
			temp = create_next_node(temp, SEMICOLON_CODE, env);
		else
			fill_node(line[i], temp);
	}
	return (root);
}

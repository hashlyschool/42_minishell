/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forest_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:56:31 by hashly            #+#    #+#             */
/*   Updated: 2022/03/31 17:58:52 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_add_redir(t_node *node, char *str, int type)
{
	t_list_redir	*content;
	char			**temp;

	content = (t_list_redir *)malloc(sizeof(t_list_redir) * 1);
	content->type_redir = type;
	if (type == 1)
		temp = ft_split_2(str, REDIR_RIGHT_ONE);
	else if (type == 2)
		temp = ft_split_2(str, REDIR_RIGHT_TWO);
	else if (type == 3)
		temp = ft_split_2(str, REDIR_LEFT_ONE);
	else
		temp = ft_split_2(str, REDIR_LEFT_TWO);
	if (temp[1] == NULL)
	{
		content->n = type <= 2;
		content->word = ft_strtrim(temp[0], "\t\n\v\f\r ");
	}
	else
	{
		content->n = ft_atoi(temp[0]);
		content->word = ft_strtrim(temp[1], "\t\n\v\f\r ");
	}
	ft_free_str_of_str(&temp);
	ft_lstadd_back(&node->list_redir, ft_lstnew(content));
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

static void	fill_node(char **str, int i, t_node *node)
{
	int	redir;

	node->exec = 0;
	redir = str_is_redirect(str, i);
	if (redir)
		ft_add_redir(node, str[i], redir);
	else if (node->data->cmd == NULL)
		node->data->cmd = ft_strdup(str[i]);
	else
		ft_add_argv(node, str[i]);
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
		ft_set_ret(2, "bash: syntax error near unexpected token `", *node->env);
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
t_node	*get_forest(char **line, char ***env)
{
	t_node	*root;
	t_node	*temp;
	int		i;

	temp = create_empty_node(env);
	temp->def_fd[0] = dup(0);
	temp->def_fd[1] = dup(1);
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
			fill_node(line, i, temp);
	}
	return (root);
}

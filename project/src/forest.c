/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:15:36 by hashly            #+#    #+#             */
/*   Updated: 2022/01/27 23:15:57 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*create_empty_node()
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->exec = 0;
	node->def_fd[0] = dup(0);
	node->def_fd[1] = dup(1);
	node->next = NULL;
	node->next_lvl = NULL;
	node->prev_lvl = NULL;
	node->data = (t_data *)malloc(sizeof(t_data));
	node->data->cmd = NULL;
	node->data->argv = NULL;
	node->data->redir = NULL;
	node->data->pipe = NONE;
	node->data->sep = NONE;
	return (node);
}

t_node	*create_node_next_lvl(t_node *node)
{
	t_node *temp;

	temp = create_empty_node();
	node->next_lvl = temp;
	temp->prev_lvl = node;
	return (temp);
}

t_node	*go_prev_lvl(t_node *node)
{
	node = node->prev_lvl;
	return (node);
}

t_node	*create_next_node(t_node *node, char separator)
{
	t_node *temp;

	temp = create_empty_node();
	temp->next_lvl = node->next_lvl;
	temp->prev_lvl = node->prev_lvl;
	if (separator != PIPE)
		temp->data->sep = separator;
	if (separator == PIPE)
	{
		temp->data->pipe = PIPE_ON_THE_LEFT;
		if (node->data->pipe == PIPE_ON_THE_LEFT)
			node->data->pipe = PIPE_BOTH_SIDES;
		else
			node->data->pipe = PIPE_ON_THE_RIGHT;
	}
	node->next = temp;
	return (temp);
}

char	str_is_redirect(char *str)
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

void	ft_add_redir(t_node *node, char *str, char type)
{
	size_t	q_str;
	size_t	i;
	char	**ret;

	q_str = 0;
	while (node->data->redir[q_str])
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
		ret[q_str] = ret[q_str] = ft_strjoin("> ", str);
	if (type == 2)
		ret[q_str] = ret[q_str] = ft_strjoin(">> ", str);
	if (type == 3)
		ret[q_str] = ret[q_str] = ft_strjoin("< ", str);
	if (type == 4)
		ret[q_str] = ret[q_str] = ft_strjoin("<< ", str);
	free(node->data->redir);
	node->data->redir = ret;
}

void	ft_add_argv(t_node *node, char *str)
{
	int	q_str;
	char	**ret;

	q_str = 0;
	while (node->data->argv && node->data->argv[q_str])
		q_str++;
	ret = (char **)malloc(sizeof(char *) * (q_str + 2));
	ret[q_str + 1] = NULL;
	ret[q_str] = ft_strdup(str);
	while (--q_str >= 0)
		ret[q_str] = node->data->argv[q_str];
	free(node->data->argv);
	node->data->argv = ret;
}

void	fill_node(char *str, t_node *node)
{
	int	redir;

	node->exec = 0;
	redir = str_is_redirect(str);
	if (node->data->cmd == NULL)
		node->data->cmd = ft_strdup(str);
	else if (redir == 1)
		ft_add_redir(node, str, 1);
	else if (redir == 2)
		ft_add_redir(node, str, 2);
	else if (redir == 3)
		ft_add_redir(node, str, 3);
	else if (redir == 4)
		ft_add_redir(node, str, 4);
	else
		ft_add_argv(node, str);
}

t_node	*get_forest(char **line)
{
	t_node	*root;
	t_node	*temp;
	size_t	i;

	temp = create_empty_node();
	root = temp;
	i = 0;
	while (line && line[i])
	{
		if (ft_strncmp(line[i], BRACKET_LEFT, ft_strlen(BRACKET_LEFT) + 1) == 0)
			temp = create_node_next_lvl(temp);
		else if (ft_strncmp(line[i], BRACKET_RIGHT, ft_strlen(BRACKET_RIGHT) + 1) == 0)
			temp = go_prev_lvl(temp);
		else if (ft_strncmp(line[i], TWO_AMPERSAND, ft_strlen(TWO_AMPERSAND) + 1) == 0)
			temp = create_next_node(temp, AND);
		else if (ft_strncmp(line[i], TWO_VERTICAL_BAR, ft_strlen(TWO_VERTICAL_BAR) + 1) == 0)
			temp = create_next_node(temp, OR);
		else if (ft_strncmp(line[i], VERTICAL_BAR, ft_strlen(VERTICAL_BAR) + 1) == 0)
			temp = create_next_node(temp, PIPE);
		else if (ft_strncmp(line[i], SEMICOLON, ft_strlen(SEMICOLON) + 1) == 0)
			temp = create_next_node(temp, SEMICOLON_CODE);
		else
			fill_node(line[i], temp);
		i++;
	}
	return (root);
}

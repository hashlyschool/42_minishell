/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:15:36 by hashly            #+#    #+#             */
/*   Updated: 2022/01/16 23:31:05 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*create_empty_node(t_node *root)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->next = NULL;
	node->next_lvl = NULL;
	node->prev_lvl = NULL;
	node->data = (t_data *)malloc(sizeof(t_data));
	node->data->argv = NULL;
	node->data->cmd = NULL;
	node->data->flag = NULL;
	node->data->pipe_redir = NONE;
	node->data->sep = NONE;
	root = node;
	return (node);
}

void	create_node_next_lvl(t_node *node)
{
	t_node *temp;

	create_empty_node(temp);
	node->next_lvl = temp;
	temp->prev_lvl = node;
	node = temp;
}

void	go_prev_lvl(t_node *node)
{
	node = node->prev_lvl;
}

void	create_next_node(char *str, t_node *node, char separator)
{
	t_node *temp;

	create_empty_node(temp);
	temp->next_lvl = node->next_lvl;
	temp->prev_lvl = node->prev_lvl;
	temp->data->sep = separator;
	node->next = temp;
	node = temp;
}

static char	*find_end(const char *start)
{
	size_t	i;
	char	in_one;
	char	in_two;

	i = 0;
	in_one = 0;
	in_two = 0;
	while (start[i])
	{
		if (start[i] == '"')
			in
		if (in_one == 0 && in_two == 0 && ( \
		(start[i] == '(' || start[i] == ')') || \
		(start[i] == '&' && start[i + 1] == '&') || \
		(start[i] == '|' && start[i + 1] == '|'))
			break;
		else
			i++;
	}
	return (start + i);
}

void	fill_node(char *start, t_node *node)
{
	char	*end;

	end = find_end(start);
}

t_node	*get_forest(const char *line)
{
	t_node	*root;
	t_node	*temp;
	size_t	i;

	temp = create_empty_node(root);
	i = 0;
	while (line && line[i])
	{
		if (ft_strncmp(line[i], "(", 2) == 0)
			create_node_next_lvl(temp);
		else if (ft_strncmp(line[i], ")", 2) == 0)
			go_prev_lvl(temp);
		else if (ft_strncmp(line[i], "&&", 3) == 0)
			create_next_node(line[i], temp, AND);
		else if (ft_strncmp(line[i], "||", 3) == 0)
			create_next_node(line[i], temp, OR);
		else if (ft_strncmp(line[i], "|", 2) == 0)
			create_next_node(line[i], temp, PIPE);
		else
			fill_node(line[i], temp);
		i++;
	}
	return (root);
}

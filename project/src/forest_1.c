/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forest_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:15:36 by hashly            #+#    #+#             */
/*   Updated: 2022/04/29 18:56:12 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*create_empty_node(char ***env, char mode)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->env = env;
	node->exec = 0;
	node->exit = 0;
	node->stop = 0;
	node->list_redir = NULL;
	node->next = NULL;
	node->next_lvl = NULL;
	node->prev_lvl = NULL;
	node->data = (t_data *)malloc(sizeof(t_data));
	node->data->cmd = NULL;
	node->data->cmd_exec = NULL;
	node->data->argv = NULL;
	node->data->pipe = NONE;
	node->data->sep = NONE;
	node->mode = mode;
	return (node);
}

t_node	*create_node_next_lvl(t_node *node, char ***env, char mode)
{
	t_node	*temp;

	temp = create_empty_node(env, mode);
	temp->def_fd[0] = node->def_fd[0];
	temp->def_fd[1] = node->def_fd[1];
	node->next_lvl = temp;
	temp->prev_lvl = node;
	return (temp);
}

t_node	*go_prev_lvl(t_node *node)
{
	node = node->prev_lvl;
	return (node);
}

t_node	*create_next_node(t_node *node, char separator, char ***env, char m)
{
	t_node	*temp;

	temp = create_empty_node(env, m);
	temp->def_fd[0] = node->def_fd[0];
	temp->def_fd[1] = node->def_fd[1];
	if (node->data->cmd)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forest_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 15:15:36 by hashly            #+#    #+#             */
/*   Updated: 2022/03/17 20:44:03 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	*create_empty_node(char **env)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->env = env;
	node->exec = 0;
	node->exit = 0;
	node->stop = 0;
	node->def_fd[0] = dup(0);
	node->def_fd[1] = dup(1);
	node->redir_fd[0] = -1;
	node->redir_fd[1] = -1;
	node->redir_fd[2] = -1;
	node->next = NULL;
	node->next_lvl = NULL;
	node->prev_lvl = NULL;
	node->data = (t_data *)malloc(sizeof(t_data));
	node->data->cmd = NULL;
	node->data->cmd_exec = NULL;
	node->data->argv = NULL;
	node->data->redir = NULL;
	node->data->pipe = NONE;
	node->data->sep = NONE;
	return (node);
}

t_node	*create_node_next_lvl(t_node *node, char **env)
{
	t_node	*temp;

	temp = create_empty_node(env);
	node->next_lvl = temp;
	temp->prev_lvl = node;
	return (temp);
}

t_node	*go_prev_lvl(t_node *node)
{
	node = node->prev_lvl;
	return (node);
}

t_node	*create_next_node(t_node *node, char separator, char **env)
{
	t_node	*temp;

	temp = create_empty_node(env);
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

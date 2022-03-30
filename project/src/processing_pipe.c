/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:38:03 by hashly            #+#    #+#             */
/*   Updated: 2022/03/30 18:25:49 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_default_fd(t_node *node)
{
	int	fd[3];

	fd[0] = dup(0);
	fd[1] = dup(1);
	fd[2] = dup(2);
	while (node)
	{
		node->def_fd[0] = fd[0];
		node->def_fd[1] = fd[1];
		node->def_fd[2] = fd[2];
		node = node->next;
	}
}

void	close_default_fd(t_node *node)
{
	close(node->def_fd[0]);
	close(node->def_fd[1]);
	close(node->def_fd[2]);
}

int	pipilene_is_over(t_list **pipeline)
{
	t_list		*temp;
	t_content	*content;

	temp = *pipeline;
	while (temp)
	{
		content = temp->content;
		if (content->pid != -1)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	processing_pipe_in_child(t_node *node)
{
	if (node->data->pipe == PIPE_ON_THE_LEFT)
	{
		close(node->pipe[1]);
		dup2(node->pipe[0], 0);
		close(node->pipe[0]);
	}
	else if (node->data->pipe == PIPE_ON_THE_RIGHT)
	{
		close(node->next->pipe[0]);
		dup2(node->next->pipe[1], 1);
		close(node->next->pipe[1]);
	}
	else if (node->data->pipe == PIPE_BOTH_SIDES)
	{
		close(node->pipe[1]);
		dup2(node->pipe[0], 0);
		close(node->pipe[0]);
		close(node->next->pipe[0]);
		dup2(node->next->pipe[1], 1);
		close(node->next->pipe[1]);
	}
}

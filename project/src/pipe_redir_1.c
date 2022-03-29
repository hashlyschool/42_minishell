/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:27:20 by hashly            #+#    #+#             */
/*   Updated: 2022/03/29 17:25:40 by hashly           ###   ########.fr       */
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

void	open_pipe_in_all_pipeline(t_node *node)
{
	t_node	*temp;

	temp = node;
	while (temp->data->pipe != PIPE_ON_THE_LEFT)
	{
		pipe(temp->next->pipe);
		temp = temp->next;
	}
}

static void	ft_set_pipe(t_node *node)
{
	if (node->data->pipe == PIPE_ON_THE_LEFT)
	{
		dup2(node->pipe[0], 0);
		dup2(node->def_fd[1], 1);
	}
	else if (node->data->pipe == PIPE_ON_THE_RIGHT)
	{
		dup2(node->next->pipe[1], 1);
		dup2(node->def_fd[0], 0);
	}
	else if (node->data->pipe == PIPE_BOTH_SIDES)
	{
		dup2(node->pipe[0], 0);
		dup2(node->next->pipe[1], 1);
	}
}

/*
Функция, которая устанавливает пайп.
редиректы еще не работают
*/
void	ft_set_redir_pipe(t_node *node)
{
	if (node->data->pipe)
		ft_set_pipe(node);
	if (node->data->redir)
		ft_set_redir(node);
}

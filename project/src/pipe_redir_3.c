/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:12:57 by hashly            #+#    #+#             */
/*   Updated: 2022/03/29 17:23:58 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_default_fd(t_node *node)
{
	close(node->def_fd[0]);
	close(node->def_fd[1]);
	close(node->def_fd[2]);
}

static void	ft_close_pipe(t_node *node)
{
	if (node->data->pipe == PIPE_ON_THE_LEFT)
	{
		close(node->pipe[0]);
		dup2(node->def_fd[0], 0);
	}
	else if (node->data->pipe == PIPE_ON_THE_RIGHT)
	{
		close(node->next->pipe[1]);
		dup2(node->def_fd[1], 1);
	}
	else if (node->data->pipe == PIPE_BOTH_SIDES)
	{
		close(node->next->pipe[1]);
		close(node->pipe[0]);
		dup2(node->def_fd[0], 0);
		dup2(node->def_fd[1], 1);
	}
}

static void	ft_close_redir(t_node *node)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (node->redir_fd[i] != -1)
		{
			close(node->redir_fd[i]);
		}
		i++;
	}
}

void	ft_close_redir_pipe(t_node *node)
{
	if (node->data->redir)
		ft_close_redir(node);
	if (node->data->pipe)
		ft_close_pipe(node);
}

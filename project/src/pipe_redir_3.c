/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:12:57 by hashly            #+#    #+#             */
/*   Updated: 2022/03/13 19:09:04 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_close_pipe(t_node *node, int *fd_left, int *fd_right)
{
	if (node->data->pipe == PIPE_ON_THE_LEFT)
	{
		fd_left = node->pipe;
		dup2(find_def_fd(node, 0), 0);
		close(fd_left[0]);
	}
	else if (node->data->pipe == PIPE_ON_THE_RIGHT)
	{
		fd_right = node->next->pipe;
		close(fd_right[1]);
		dup2(find_def_fd(node, 1), 1);
		dup2(fd_right[0], 0);
	}
	else if (node->data->pipe == PIPE_BOTH_SIDES)
	{
		fd_left = node->pipe;
		close(fd_left[0]);
		dup2(find_def_fd(node, 0), 0);
		fd_right = node->next->pipe;
		close(fd_right[1]);
		dup2(find_def_fd(node, 1), 1);
		dup2(fd_right[0], 0);
	}
}

static void	ft_close_redir(t_node *node)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (node->redir_fd[i] != -1)
			close(node->redir_fd[i]);
		i++;
	}
	dup2(find_def_fd(node, 1), 1);
	dup2(find_def_fd(node, 0), 0);
}

/*
Функция, которая закрывает пайпы.
редиректы еще не работают
*/
void	ft_close_redir_pipe(t_node *node)
{
	int	*fd_left;
	int	*fd_right;

	fd_right = NULL;
	fd_left = NULL;
	if (node->data->pipe)
		ft_close_pipe(node, fd_left, fd_right);
	if (node->data->redir)
		ft_close_redir(node);
}

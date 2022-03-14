/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:27:20 by hashly            #+#    #+#             */
/*   Updated: 2022/03/13 18:38:36 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_def_fd(t_node *node, int fd)
{
	t_node	*temp;
	char	pipe;

	temp = node;
	while (temp && temp->next)
		temp = temp->next;
	if (temp->prev_lvl && temp->prev_lvl->data->pipe)
	{
		temp = temp->prev_lvl;
		pipe = temp->data->pipe;
		if (fd == 0 && (pipe == PIPE_ON_THE_LEFT || pipe == PIPE_BOTH_SIDES))
			return (temp->pipe[0]);
		if (fd == 1 && (pipe == PIPE_ON_THE_RIGHT || pipe == PIPE_BOTH_SIDES))
			return (temp->pipe[1]);
	}
	return (node->def_fd[fd]);
}

static void	ft_set_pipe(t_node *node, int *fd_left, int *fd_right)
{
	fd_left = node->pipe;
	if (node->data->pipe == PIPE_ON_THE_LEFT)
		return ;
	else if (node->data->pipe == PIPE_ON_THE_RIGHT)
	{
		fd_right = node->next->pipe;
		pipe(fd_right);
		dup2(fd_right[1], 1);
	}
	else if (node->data->pipe == PIPE_BOTH_SIDES)
	{
		fd_right = node->next->pipe;
		pipe(fd_right);
		dup2(fd_right[1], 1);
	}
}

/*
Функция, которая устанавливает пайп.
редиректы еще не работают
*/
void	ft_set_redir_pipe(t_node *node)
{
	int	*fd_left;
	int	*fd_right;

	fd_right = NULL;
	fd_left = NULL;
	if (node->data->pipe)
		ft_set_pipe(node, fd_left, fd_right);
	if (node->data->redir)
		ft_set_redir(node);
}

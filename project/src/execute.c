/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:52:50 by hashly            #+#    #+#             */
/*   Updated: 2022/01/27 23:48:02 by hashly           ###   ########.fr       */
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

void	ft_set_redir_pipe(t_node *node)
{
	int	*fd_left;
	int	*fd_right;

	if (node->data->pipe || node->data->redir)
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
}

void	ft_close_redir_pipe(t_node *node)
{
	int	*fd_left;
	int	*fd_right;

	if (node->data->pipe || node->data->redir)
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
}

void	ft_execve(t_node *node)
{
	if (node->data)
		return ;
	return ;
}

void	action(t_node *node)
{
	node->exec = 1;
	if (cond_status(node))
		return ;
	if (cond_is_built_in(node) == 0)
		;
	else
		ft_execve(node);
}

void	execute(t_node *node, void (*action)(t_node *))
{
	t_node * temp;

	while (node->exec != 1)
	{
		temp = node;
		ft_set_redir_pipe(temp);
		if (node->next_lvl && node->exec == 0)
			node = node->next_lvl;
		else if (node->next)
		{
			action(node);
			node = node->next;
		}
		else if (node->prev_lvl)
		{
			action(node);
			node = node->prev_lvl;
			node->exec = 1;
		}
		if (temp->exec == 1)
			ft_close_redir_pipe(temp);
		if (!node->prev_lvl && !node->next && node->exec == 0)
		{
			action(node);
			ft_close_redir_pipe(node);
		}
	}
}

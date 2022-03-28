/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:12:57 by hashly            #+#    #+#             */
/*   Updated: 2022/03/28 20:14:36 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_close_pipe(t_node *node)
{
	if (node->data->pipe == PIPE_ON_THE_LEFT)
	{
		close(node->pipe[0]);
		// dup2(node->def_fd[0], 0);
	}
	else if (node->data->pipe == PIPE_ON_THE_RIGHT)
	{
		close(node->next->pipe[1]);
		// dup2(node->def_fd[1], 1);
	}
	else if (node->data->pipe == PIPE_BOTH_SIDES)
	{
		close(node->next->pipe[1]);
		close(node->pipe[0]);
		// dup2(node->def_fd[0], 0);
		// dup2(node->def_fd[1], 1);
	}
// else if (node->data->pipe == PIPE_ON_THE_RIGHT)
// {
// 	fd_right = node->next->pipe;
// 	close(fd_right[1]);
// 	dup2(find_def_fd(node, 1), 1);
// 	dup2(fd_right[0], 0);
// }
// else if (node->data->pipe == PIPE_BOTH_SIDES)
// {
// 	fd_left = node->pipe;
// 	close(fd_left[0]);
// 	dup2(find_def_fd(node, 0), 0);
// 	fd_right = node->next->pipe;
// 	close(fd_right[1]);
// 	dup2(find_def_fd(node, 1), 1);
// 	dup2(fd_right[0], 0);
// }
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
			// node->redir_fd[i] = -1;
		}
		i++;
	}
	// if (node->next && node->next->pipe[0] != -1)
	// 	dup2(node->next->pipe[0], 0);
	// if (node->next && node->next->pipe[1] != -1)
	// 	dup2(node->next->pipe[1], 1);
}

void	check_zombie_process_and_close_pipe_redir(t_list **list_fd)
{
	pid_t	pid;

	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(-1, NULL, WNOHANG);
		errno = 0;
		if (pid > 0)
			ft_close_redir_pipe_to_fd(pid, list_fd);
	}
}

void	ft_close_redir_pipe_to_fd(pid_t pid, t_list **list_fd)
{
	t_list		*temp_list;
	t_content	*temp_cont;

	temp_list = *list_fd;
	while (temp_list)
	{
		temp_cont = (t_content *)temp_list->content;
		if (temp_cont->pid == pid)
		{
			ft_close_redir_pipe(temp_cont->node);
			temp_cont->pid = -1;
			// ft_lstdelone(temp_list, &free);
			return ;
		}
		temp_list = temp_list->next;
	}
}

void	ft_close_redir_pipe(t_node *node)
{
	if (node->data->redir)
		ft_close_redir(node);
	if (node->data->pipe)
		ft_close_pipe(node);
}

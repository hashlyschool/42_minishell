/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:12:57 by hashly            #+#    #+#             */
/*   Updated: 2022/03/27 22:25:33 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_close_pipe(t_node *node)
{
	if (node->data->pipe == PIPE_ON_THE_LEFT || \
	node->data->pipe == PIPE_BOTH_SIDES)
		close(node->pipe[0]);
	if (node->data->pipe == PIPE_ON_THE_RIGHT || \
	node->data->pipe == PIPE_BOTH_SIDES)
		close(node->next->pipe[1]);
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
			close(node->redir_fd[i]);
		i++;
	}

}

/*
Функция, которая закрывает пайпы и редиректы.
*/
void	ft_close_redir_pipe(t_node *node)
{
	if (node->data->redir)
		ft_close_redir(node);
	if (node->data->pipe)
		ft_close_pipe(node);
	dup2(node->def_fd[0], 0);
	dup2(node->def_fd[1], 1);
	dup2(node->def_fd[2], 2);
}

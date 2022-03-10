/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:27:20 by hashly            #+#    #+#             */
/*   Updated: 2022/03/10 16:24:13 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	find_def_fd(t_node *node, int fd)
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

/*
-1	error
1	>
2	>>
3	<
4	<<
*/
static int	find_code(char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (2);
		return (1);
	}
	else if (str[0] == '<')
	{
		if (str[1] == '<')
			return (4);
		return (3);
	}
	return (-1);
}

static void	ft_set_redir(t_node *node)
{
	size_t	i;
	int		code;
	// int		fd;

	i = 0;
	while (node->data->redir[i])
	{
		code = find_code(node->data->redir[i]);
		// if (code == 2)
		// 	fd = open(node->data->redir[i] + code + 1, O_WRONLY | O_CREAT | O_APPEND);
		i++;

	}

}

static void	ft_close_redir(t_node *node)
{
	size_t	i;

	i = 0;
	while (node->data->redir[i])
	{
		i++;
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

	if (node->data->redir)
		ft_set_redir(node);
	else if (node->data->pipe)
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

/*
Функция, которая закрывает пайпы.
редиректы еще не работают
*/
void	ft_close_redir_pipe(t_node *node)
{
	int	*fd_left;
	int	*fd_right;

	if (node->data->redir)
		ft_close_redir(node);
	else if (node->data->pipe)
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

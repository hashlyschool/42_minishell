/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:52:50 by hashly            #+#    #+#             */
/*   Updated: 2022/04/09 22:50:53 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	execute_child_node(t_node *node)
{
	processing_pipe_in_child(node);
	ft_set_redir(node);
	execute_cmd_in_node(node);
	ft_close_redir(node);
	if (node->data->pipe == PIPE_ON_THE_LEFT)
		exit(ft_atoi(ft_get_status(*node->env)));
	exit(0);
}

static void	processing_exit_code(t_list **pipeline, pid_t pid, int ret)
{
	t_content	*content;
	t_list		*temp;

	temp = *pipeline;
	while (temp)
	{
		content = temp->content;
		if (content->pid == pid)
		{
			if (temp->next == NULL)
			{
				if (WIFSIGNALED(ret))
					ft_set_ret(130, NULL, *content->node->env);
				else if (WIFEXITED(ret))
					ft_set_ret(WEXITSTATUS(ret), NULL, *content->node->env);
			}
			content->pid = -1;
			return ;
		}
		temp = temp->next;
	}
}

static void	execute_parent_node(t_node *node, pid_t pid, t_list **pipeline)
{
	int			ret;
	t_content	*content;

	content = (t_content *)malloc(sizeof(t_content) * 1);
	content->node = node;
	content->pid = pid;
	ft_lstadd_back(pipeline, ft_lstnew(content));
	if (node->data->pipe == PIPE_ON_THE_LEFT)
	{
		while (1)
		{
			pid = waitpid(-1, &ret, 0);
			if (pid > 0)
				processing_exit_code(pipeline, pid, ret);
			if (pipilene_is_over(pipeline))
			{
				ft_lstclear(pipeline, &free);
				*pipeline = NULL;
				return ;
			}
		}
	}
}

static void	execute_node_or_pipe(t_node *node, t_list **pipeline)
{
	pid_t		pid;

	if (node->data->pipe)
	{
		if (node->data->pipe == PIPE_ON_THE_RIGHT || \
		node->data->pipe == PIPE_BOTH_SIDES)
			pipe(node->next->pipe);
		pid = fork();
		if (pid == 0)
			execute_child_node(node);
		if (node->data->pipe == PIPE_ON_THE_LEFT || \
		node->data->pipe == PIPE_BOTH_SIDES)
		{
			close(node->pipe[0]);
			close(node->pipe[1]);
		}
		execute_parent_node(node, pid, pipeline);
	}
	else
	{
		ft_set_redir(node);
		execute_cmd_in_node(node);
		ft_close_redir(node);
	}
}

void	execute_level(t_node *node)
{
	t_list	*pipeline;

	set_default_fd(node);
	pipeline = NULL;
	while (node && !node->exit)
	{
		execute_node_or_pipe(node, &pipeline);
		if (node->next == NULL)
			close_default_fd(node);
		if (!node->exit)
			node = node->next;
	}
}

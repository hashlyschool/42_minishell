/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:21:17 by hashly            #+#    #+#             */
/*   Updated: 2022/03/29 17:22:32 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	processing_exit_code(t_list **pipeline, pid_t pid, int ret)
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
			ft_close_redir_pipe(content->node);
			content->pid = -1;
			return ;
		}
		temp = temp->next;
	}
}

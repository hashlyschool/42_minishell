/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:39:21 by hashly            #+#    #+#             */
/*   Updated: 2022/03/31 17:51:14 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_close_redir(t_node *node)
{
	t_list			*temp;
	t_list_redir	*content;

	temp = node->list_redir;
	while (temp)
	{
		content = temp->content;
		if (content->fd >= 0)
			close(content->fd);
		free(content->word);
		temp = temp->next;
	}
	dup2(node->def_fd[0], 0);
	dup2(node->def_fd[1], 1);
	dup2(node->def_fd[2], 2);
	ft_lstclear(&node->list_redir, &free);
}


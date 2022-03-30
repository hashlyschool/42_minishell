/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:39:21 by hashly            #+#    #+#             */
/*   Updated: 2022/03/30 18:43:13 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_close_redir(t_node *node)
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
	dup2(node->def_fd[0], 0);
	dup2(node->def_fd[1], 1);
}


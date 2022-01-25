/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:52:50 by hashly            #+#    #+#             */
/*   Updated: 2022/01/25 23:21:38 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_set_redir(t_node *node)
{

}

void	ft_set_pipe(t_node *node)
{

}

void	ft_execve(t_node *node)
{

}

void	action(t_node *node)
{
	if (!node)
		return ;
	if (ft_condition_status(node))
		return ;
	if (node->data->redir)
		ft_set_redir(node);
	if (node->data->pipe)
		ft_set_pipe(node);
	if (cond_is_built_in(node))
		return ;
	else
		ft_execve(node);
	return ;
}

void	execute(t_node *node, void (*action)(t_node *))
{
	while (node->next_lvl || node->prev_lvl || node->next)
	{
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
		if (node->exec == 1 && !node->prev_lvl && !node->next)
			break;
	}
	action(node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:52:50 by hashly            #+#    #+#             */
/*   Updated: 2022/02/12 18:02:29 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_execve(t_node *node)
{
	if (node->data)
		return ;
	return ;
}

void	action(t_node *node)
{
	node->exec = 1;
	if (cond_status(node)) //+
		return ;
	preparsing(node); //+- MASHA
	if (cond_is_built_in(node) == 0) //+-
		;
	else
		ft_execve(node); //-
}
/*
Функция принимает указатель на корень дерева.
В зависимости от содержимого и структуры дерева происходит
выполнение соответствующих операций
*/
void	execute(t_node *node)
{
	t_node * temp;

	while (node->exec != 1)
	{
		temp = node;
		ft_set_redir_pipe(temp); //+-
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
			ft_close_redir_pipe(temp);//+-
		if (!node->prev_lvl && !node->next && node->exec == 0 && \
		node->data->cmd)
		{
			action(node);
			ft_close_redir_pipe(node);//+-
		}
	}
}

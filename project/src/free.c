/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:53:53 by hashly            #+#    #+#             */
/*   Updated: 2022/02/12 16:04:37 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Функция для освобождения массива строк и зануления указателя
*/
void	free_cmd_line(char ***arg)
{
	char	**arr;
	size_t	i;

	i = 0;
	arr = *arg;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	arr = NULL;
	return ;
}

/*
Функция для освобождения узла дерева
*/
void	free_node(t_node *node)
{
	size_t	i;
	t_data	*data;

	i = 0;
	data = node->data;
	if (!node->next_lvl)
	{
		if (data->argv)
		{
			while (data->argv[i])
				free(data->argv[i++]);
			free(data->argv);
		}
		i = 0;
		if (data->redir)
		{
			while (data->redir[i])
				free(data->redir[i++]);
			free(data->redir);
		}
		if (data->cmd)
			free(data->cmd);
	}
	free(data);
	free(node);
}

/*
Функция для освобождения памяти под дерево
*/
void	free_forest(t_node *temp)
{
	t_node	*for_free;

	while (temp->next_lvl || temp->prev_lvl || temp->next)
	{
		for_free = temp;
		if (temp->next_lvl)
		{
			temp = temp->next_lvl;
			for_free->next_lvl = NULL;
		}
		else if (temp->next)
		{
			temp = temp->next;
			free_node(for_free);
		}
		else if (temp->prev_lvl)
		{
			temp = temp->prev_lvl;
			free_node(for_free);
		}
	}
	free_node(temp);
}

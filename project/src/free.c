/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:53:53 by hashly            #+#    #+#             */
/*   Updated: 2022/04/29 17:36:58 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_arr_export(char ***key, char ***value)
{
	size_t	i;

	i = 0;
	while (key[0][i])
	{
		free(key[0][i++]);
		if (value[0][i - 1])
			free(value[0][i - 1]);
	}
	free(key[0]);
	free(value[0]);
}

static void	free_node_2(t_data *data)
{
	if (data->cmd)
		free(data->cmd);
	if (data->cmd_exec)
		free(data->cmd_exec);
}

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
		free_node_2(data);
	}
	if (node->list_redir)
		ft_lstclear(&node->list_redir, &free_node_list_redir);
	close(node->def_fd[0]);
	close(node->def_fd[1]);
	free(data);
	free(node);
}

void	free_forest(t_node *temp, char ****env)
{
	t_node	*for_free;

	*env = temp->env;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 13:30:50 by hashly            #+#    #+#             */
/*   Updated: 2022/04/28 16:35:40 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_spase_define(t_node *node)
{
	char	*new_str;

	new_str = ft_strnstr(node->data->cmd,
			START_DOUBLE_QUOTE, ft_strlen(node->data->cmd));
	while (new_str != NULL)
	{
		node->data->cmd = ft_queote_dollar(node->data->cmd, new_str, 0);
		new_str = ft_strnstr(node->data->cmd,
				START_DOUBLE_QUOTE, ft_strlen(node->data->cmd));
	}
	new_str = ft_strnstr(node->data->cmd,
			END_DOUBLE_QUOTE, ft_strlen(node->data->cmd));
	while (new_str != NULL)
	{
		node->data->cmd = ft_queote_dollar(node->data->cmd, new_str, 1);
		new_str = ft_strnstr(node->data->cmd,
				END_DOUBLE_QUOTE, ft_strlen(node->data->cmd));
	}
}

static void	delete_spase_define3(t_node *node, char **new_str, int *i)
{
	while (*new_str != NULL)
	{
		node->data->argv[*i] = ft_queote_dollar(node->data->argv[*i],
				*new_str, 1);
		*new_str = ft_strnstr(node->data->argv[*i],
				END_DOUBLE_QUOTE, ft_strlen(node->data->argv[*i]));
	}
}

void	delete_spase_define2(t_node *node)
{
	char	*new_str;
	int		i;

	i = 0;
	while (node->data->argv[i])
	{
		new_str = ft_strnstr(node->data->argv[i],
				START_DOUBLE_QUOTE, ft_strlen(node->data->argv[i]));
		while (new_str != NULL)
		{
			node->data->argv[i] = ft_queote_dollar(node->data->argv[i],
					new_str, 0);
			new_str = ft_strnstr(node->data->argv[i],
					START_DOUBLE_QUOTE, ft_strlen(node->data->argv[i]));
		}
		new_str = ft_strnstr(node->data->argv[i],
				END_DOUBLE_QUOTE, ft_strlen(node->data->argv[i]));
		delete_spase_define3(node, &new_str, &i);
		i++;
	}
}

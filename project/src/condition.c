/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:56:14 by hashly            #+#    #+#             */
/*   Updated: 2022/01/27 23:38:56 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	cond_status(t_node	*node)
{
	int	status;

	status = ft_get_status();
	if (node->data->sep == NONE || node->data->sep == SEMICOLON_CODE)
		return (0);
	if (status == 0 && node->data->sep == AND)
		return (0);
	if (status != 0 && node->data->sep == OR)
		return (0);
	return (1);
}

int	cond_is_built_in(t_node *node)
{
	if (ft_strncmp(node->data->cmd, "echo", 5) == 0)
		ft_echo(node->data->argv);
	// else if (ft_strncmp(node->data->cmd, "cd", 3) == 0)
	// 	ft_cd(node->data->argv);
	// else if (ft_strncmp(node->data->cmd, "pwd", 4) == 0)
	// 	ft_pwd(node->data->argv);
	// else if (ft_strncmp(node->data->cmd, "export", 7) == 0)
	// 	ft_export(node->data->argv);
	// else if (ft_strncmp(node->data->cmd, "unset", 6) == 0)
	// 	ft_unset(node->data->argv);
	// else if (ft_strncmp(node->data->cmd, "env", 4) == 0)
	// 	ft_env(node->data->argv);
	// else if (ft_strncmp(node->data->cmd, "exit", 5) == 0)
	// 	ft_exit(node->data->argv);
	else
		return (0);
	return (1);
}

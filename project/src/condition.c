/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:56:14 by hashly            #+#    #+#             */
/*   Updated: 2022/02/20 19:40:44 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*

*/
int	cmd_in_path(t_node *node)
{
	char	*path;
	char	flag_path;
	char	flag_abs_rel_path;

	path = ft_getenv("PATH", node->env);
	flag_path = 1;
	flag_abs_rel_path = 1;
	if (!path)
		flag_path = 0;
	if (ft_strnstr(node->data->cmd, "./", 2) == NULL && \
	ft_strnstr(node->data->cmd, "../", 3) == NULL && \
	ft_strnstr(node->data->cmd, "/", ft_strlen(node->data->cmd)) == NULL)
		flag_abs_rel_path = 0;
	if (flag_path && !flag_abs_rel_path)
		return (1);
	if (ft_strnstr(node->data->cmd, "./", 2) == NULL && \
	ft_strnstr(node->data->cmd, "../", 3) == NULL && \
	ft_strnstr(node->data->cmd, "/", 1) == NULL)
		node->data->cmd = ft_strjoin_free_s2("./", node->data->cmd);
	return (0);
}

/*
Функция, которая возвращает 0, если нужно выполнять команду
иначе 1
*/
int	cond_status(t_node	*node)
{
	int	status;

	status = ft_atoi(ft_get_status(node->env));
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
		ft_echo(node->data->argv, node->env);
	// else if (ft_strncmp(node->data->cmd, "cd", 3) == 0)
	// 	ft_cd(node->data->argv, node->env);
	// else if (ft_strncmp(node->data->cmd, "pwd", 4) == 0)
	// 	ft_pwd(node->data->argv, node->env);
	// else if (ft_strncmp(node->data->cmd, "export", 7) == 0)
	// 	ft_export(node->data->argv, node->env);
	// else if (ft_strncmp(node->data->cmd, "unset", 6) == 0)
	// 	ft_unset(node->data->argv, node->env);
	// else if (ft_strncmp(node->data->cmd, "env", 4) == 0)
	// 	ft_env(node->data->argv, node->env);
	// else if (ft_strncmp(node->data->cmd, "exit", 5) == 0)
	// 	ft_exit(node->data->argv, node->env);
	else
		return (0);
	return (1);
}

int	node_is_not_empty(t_node *root)
{
	if (!root->next && !root->next_lvl && !root->prev_lvl && \
	!root->data->cmd)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/01/23 15:51:01 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_cmd_line(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return ;
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

void	action(t_node *node)
{
	ft_putstr_fd("cmd: ", 1);
	ft_putstr_fd(node->data->cmd, 1);
	ft_putstr_fd("\n", 1);
	if (node->data->redir)
	{
		ft_putstr_fd("\nredir: ", 1);
		ft_putstr_fd(node->data->redir[0], 1);
		ft_putstr_fd("\n", 1);
	}
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

int	main(int argc, char **argv, char **envp)
{
	char	**cmd_line;
	t_node	*root;

	g_envp = ft_copy_env(envp);
	argv = NULL;
	if (argc != 1)
		return (0);
	set_signal();
	while (1)
	{
		cmd_line = parsing(); //Masha
		root = get_forest(cmd_line); //ILYA
		free_cmd_line(cmd_line); //+
		execute(root, action); //ILYA
		free_forest(root); //ILYA
	}
	return (0);
}

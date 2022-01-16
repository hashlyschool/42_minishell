/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/01/16 23:22:18 by hashly           ###   ########.fr       */
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

void	free_forest(t_node *root)
{
	root = 0;
	return ;
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
		execute(root); //ILYA
		free_forest(root); //ILYA
	}
	return (0);
}

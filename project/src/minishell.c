/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/02/23 00:28:26 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmd_line;
	t_node	*root;
	char	**env;

	if (argc != 1)
	{
		ft_putstr_fd("minishel: Invalid number of arguments\n", 1);
		return (0);
	}
	env = ft_copy_env(envp);
	argv = NULL;
	set_signal();
	while (1)
	{
		cmd_line = parsing(env);
		root = get_forest(cmd_line, env);
		free_cmd_line(&cmd_line);
		if (node_is_not_empty(root))
			execute(root);
		free_forest(root);
	}
	return (0);
}

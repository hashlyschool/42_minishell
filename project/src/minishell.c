/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/02/13 16:54:03 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	**cmd_line;
	t_node	*root;
	char	**env;

	env = ft_copy_env(envp);
	argv = NULL;
	if (argc != 1)
		return (0);
	set_signal();
	while (1)
	{
		cmd_line = parsing(env); //Masha
		root = get_forest(cmd_line, env); //ILYA
		free_cmd_line(&cmd_line); //+
		if (node_is_not_empty(root))
			execute(root); //ILYA //MASHA
		free_forest(root); //ILYA
	}
	return (0);
}

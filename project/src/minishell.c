/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/02/24 03:57:05 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_check_status_exit(char status_exit, char ***env)
{
	if (status_exit)
	{
		status_exit = (char)(ft_atoi(ft_get_status(*env)));
		ft_free_envp(*env);
		// rl_clear_history();
		exit(status_exit);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd_line;
	t_node	*root;
	char	**env;
	char	status_exit;

	if (argc != 1)
	{
		ft_putstr_fd("minishel: Invalid number of arguments\n", 1);
		return (0);
	}
	env = ft_copy_env(envp, &argv);
	status_exit = 0;
	set_signal();
	while (1)
	{
		ft_check_status_exit(status_exit, &env);
		cmd_line = parsing(env);
		root = get_forest(cmd_line, env);
		free_cmd_line(&cmd_line);
		if (node_is_not_empty(root))
			execute(root);
		status_exit = root->exit;
		free_forest(root, &env);
	}
	return (0);
}

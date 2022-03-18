/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/03/18 21:13:15 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_check_status_exit(char status_exit, char ***env)
{
	if (status_exit)
	{
		status_exit = (char)(ft_atoi(ft_get_status(*env)));
		ft_free_envp(*env);
		#ifdef __APPLE__
		clear_history();
		#elif __linux__
		rl_clear_history();
		#endif
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
		ft_putstr_fd(PROGRAM_NAME": Invalid number of arguments\n", 1);
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
		ft_free_str_of_str(&cmd_line);
		if (node_is_not_empty(root))
			execute(root);
		status_exit = root->exit;
		free_forest(root, &env);
	}
	return (0);
}

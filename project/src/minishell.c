/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/04/05 02:55:42 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_check_status_exit(char status_exit, char ****env)
{
	if (status_exit)
	{
		status_exit = (char)(ft_atoi(ft_get_status(**env)));
		ft_free_envp(env);
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
	char	***env;
	char	status_exit;

	#ifdef	TESTER
		rl_outstream = stderr;
	#endif
	if (argc != 1)
		ft_putstr_fd(PROGRAM_NAME": Invalid number of arguments\n", STD_ERR);
	else
	{
		env = ft_copy_env(envp, &argv);
		status_exit = 0;
		set_signal();
		while (1)
		{
			ft_check_status_exit(status_exit, &env);
			cmd_line = parsing(env);
			// ft_print_str_of_str(cmd_line);
			root = get_forest(cmd_line, env);
			ft_free_str_of_str(&cmd_line);
			if (node_is_not_empty(root))
				execute_level(root);
			status_exit = root->exit;
			free_forest(root, &env);
		}
	}
	return (0);
}

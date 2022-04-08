/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/04/08 14:11:28 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_check_status_exit(char status_exit, char ****env, char *mode_work)
{
	if (*mode_work)
		(*mode_work)++;
	if (status_exit || *mode_work == 3)
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
	char	mode_work;

	#ifdef	TESTER
		rl_outstream = stderr;
	#endif
	mode_work = 0;
	if (argc != 1)
	{
		if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
			mode_work = 1;
		else
		{
			ft_putstr_fd(PROGRAM_NAME": Invalid number of arguments\n", STD_ERR);
			return (0);
		}
	}
	env = ft_copy_env(envp);
	status_exit = 0;
	set_signal();
	while (1)
	{
		ft_check_status_exit(status_exit, &env, &mode_work);
		if (mode_work)
			cmd_line = parsing(env, argv[2], mode_work);
		else
			cmd_line = parsing(env, NULL, mode_work);
		// ft_print_str_of_str(cmd_line);
		root = get_forest(cmd_line, env);
		ft_free_str_of_str(&cmd_line);
		if (node_is_not_empty(root))
			execute_level(root);
		status_exit = root->exit;
		free_forest(root, &env);
	}
	return (0);
}

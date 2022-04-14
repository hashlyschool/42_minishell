/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/04/14 23:54:06 by a79856           ###   ########.fr       */
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
		#ifndef TESTER
		clear_history();
		#endif
		#elif __linux__
		rl_clear_history();
		#endif
		exit(status_exit);
	}
}

static char	processing_argc(int argc, char **argv)
{
	if (argc != 1)
	{
		if (argc == 3 && ft_strncmp(argv[1], "-c", 3) == 0)
			return (1);
		else
		{
			ft_putstr_fd(PROGRAM_NAME": Invalid number of arguments\n", STD_ERR);
			exit(0);
		}
	}
	return (0);
}

static void	add_pwd_shlvl_mode_c(char ****env, char	mode_work)
{
	char	**arg;
	char	*temp;

	arg = NULL;
	if (mode_work)
	{
		temp = ft_strdup("SHLVL=1");
		arg = ft_add_line(arg, temp);
		free(temp);
		temp = ft_strdup("PWD=");
		temp = ft_strjoin_free_all(temp, getcwd(NULL, 1024));
		arg = ft_add_line(arg, temp);
		ft_export(arg, env);
		free(temp);
		ft_free_str_of_str(&arg);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd_line;
	t_node	*root;
	char	***env;
	char	status_exit;
	char	mode_work;

	mode_work = processing_argc(argc, argv);
	env = ft_copy_env(envp);
	add_pwd_shlvl_mode_c(&env, mode_work);
	// ft_export("_=/usr/bin/bash", &env);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/01/16 14:40:13 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	set_data(void)
{
	t_data	data;

	data.argv = (char **)malloc(sizeof(char *) * 3);
	data.argv[0] = ft_strdup("first");
	data.argv[1] = ft_strdup("inc");
	data.argv[2] = NULL;
	data.flag = (char **)malloc(sizeof(char *) * 3);
	data.flag[0] = ft_strdup("-t");
	data.flag[1] = ft_strdup("-a");
	data.flag[2] = NULL;
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_line;
	// t_list	*cmd_list;
	t_data	data;

	data = set_data();
	g_envp = ft_copy_env(envp);
	argv = NULL;
	if (argc != 1)
		return (0);
	set_signal();
	while (1)
	{
		cmd_line = get_line();
		if (ft_strncmp(cmd_line, "echo", 4) == 0)
			ft_echo(&data);
		if (ft_strncmp(cmd_line, "pwd", 3) == 0)
			ft_pwd(&data);
		if (ft_strncmp(cmd_line, "cd", 2) == 0)
			ft_cd(&data);
		// cmd_list = split_on_cmd(cmd_line);
		free(cmd_line);
	}
	return (0);
}

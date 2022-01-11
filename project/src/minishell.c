/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 19:45:08 by hashly            #+#    #+#             */
/*   Updated: 2022/01/11 17:54:29 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main()
{
	char	*cmd_line;
	// t_list	*cmd_list;

	// argv = NULL;
	// if (argc != 1)
	// 	return (0);
	set_signal();
	// printf("%s\n", envp[0]);
	while (1)
	{
		cmd_line = get_line();
		// cmd_list = split_on_cmd(cmd_line);
		free(cmd_line);
	}
	return (0);
}

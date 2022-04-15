/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:54:17 by hashly            #+#    #+#             */
/*   Updated: 2022/04/15 10:54:44 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_handling(int mode, t_node *node, char **path)
{
	if (path)
		ft_free_str_of_str(&path);
	if (mode == 1 || mode == -1)
		output_error(1, node);
	if (mode == 0)
		output_error(2, node);
}

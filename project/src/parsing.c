/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/01/15 14:13:37 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_line(void)
{
	char	*line_read;
	char	*promt;

	promt = get_promt();
	line_read = readline(promt);
	free(promt);
	if (line_read && *line_read)
		add_history (line_read);
	if (!line_read)
		sig_d(0);
	return (line_read);
}

t_list	*split_on_cmd(char *str)
{
	t_list	*list;
	t_data	temp;

	temp.cmd = str;
	temp.pipe = 0;
	list = ft_lstnew(&temp);
	return (list);
}

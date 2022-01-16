/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/01/16 23:43:07 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_line(void)
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

char	**parsing(void)
{
	char	*str;
	char	**ret;

	str = get_line(); //+
	// ret = split_str(str); //- Masha
	ret = ft_split(str, ' ');
	free(str); //+
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 22:12:09 by hashly            #+#    #+#             */
/*   Updated: 2022/01/23 15:41:17 by hashly           ###   ########.fr       */
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

/*
cmd\0
option or argv\0
\1\2>\3\4	file_name
\1\2>>\3\4	file_name
\1\2<\3\4	file_name
\1\2<<\3\4	file_name
(
)
&&
||
|
;
NULL
*/
char **split_str(char *str)
{
	return (ft_split(str, ' '));
}

char	**parsing(void)
{
	char	*str;
	char	**ret;

	str = get_line(); //+
	ret = split_str(str); //- Masha
	free(str); //+
	return (ret);
}

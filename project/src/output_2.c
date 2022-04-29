/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:54:17 by hashly            #+#    #+#             */
/*   Updated: 2022/04/29 18:39:56 by hashly           ###   ########.fr       */
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

static char	*get_str(char *word, int i, int j)
{
	char	*str;
	char	**start;
	char	**end;

	str = ft_strdup("$");
	start = ft_split_2(word, START_VALUE);
	while (start[++i])
	{
		end = ft_split_2(start[i], END_VALUE);
		j = -1;
		while (end[++j])
		{
			str = ft_strjoin_free_s1(str, end[i]);
		}
		ft_free_str_of_str(&end);
	}
	ft_free_str_of_str(&start);
	return (str);
}

void	err_1(t_list_redir **content, t_node *node, char ***arr, char **word)
{
	char	*str;

	str = get_str((*content)->word, -1, -1);
	ft_set_ret(1, PROGRAM_NAME": ", *node->env);
	ft_putstr_fd(str, STD_ERR);
	ft_putstr_fd(": ambiguous redirect\n", STD_ERR);
	ft_free_str_of_str(arr);
	node->exec = 1;
	free(*word);
	free(str);
	return ;
}

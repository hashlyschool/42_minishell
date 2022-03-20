/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:10:33 by hashly            #+#    #+#             */
/*   Updated: 2022/03/20 16:44:46 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	replace_data_in_node(char ***arr, t_node *node)
{
	size_t	i;
	char	**temp;

	i = 0;
	temp = *arr;
	free(node->data->cmd);
	ft_free_str_of_str(&(node->data->argv));
	i = 0;
	if (temp && temp[i])
		node->data->cmd = ft_strdup(temp[i++]);
	while (temp && temp[i])
	{
		ft_add_argv(node, temp[i]);
		i++;
	}
}

/*
Masha
Функция должна разделить строку по правилам разделения bash,
затем очитстить указатель end_str и вернуть ret
if end_str из одних пробелов, то все ок
*/
char	**split_cmd_line(char **end_str)
{
	char	**ret;
	int		i;

	ret = NULL;
	i = 0;
	while (*end_str[i] == '\t' || *end_str[i] == '\n' || *end_str[i] == '\v' \
	 || *end_str[i] == '\f' || *end_str[i] == '\r' || *end_str[i] == ' ')
	 	i++;
	if ((*end_str)[i] == 0)
		ret = ft_add_line(ret, "");
	else
		ret = ft_minishell_split(*end_str);
	free(*end_str);
	return (ret);
}

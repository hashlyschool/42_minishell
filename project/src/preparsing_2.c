/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:10:33 by hashly            #+#    #+#             */
/*   Updated: 2022/04/04 21:46:45 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_error_in_env_name(char *name, char *flag)
{
	int	i;

	*flag = 0;
	i = 0;
	if (name && ft_isdigit(name[0]) && name[1] == 0)
		return (*flag);
	if (name && name [0] == 0)
	{
		*flag = 1;
		return (*flag);
	}
	while (name[i])
	{
		if (ft_isalpha(name[i]) || (ft_isdigit(name[i]) && i > 0)
			|| name[i] == '_')
			i++;
		else
		{
			*flag = 1;
			break ;
		}
	}
	return (*flag);
}

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
	char	*new;
	int		i;

	i = 0;
	ret = NULL;
	new = NULL;
	if (ft_strncmp(end_str[i], START_DOUBLE_QUOTE, ft_strlen(START_DOUBLE_QUOTE)) == 0)
	{
		new = ft_strtrim(end_str[i], START_DOUBLE_QUOTE);
		new = ft_strtrim(end_str[i], END_DOUBLE_QUOTE);
		free(*end_str);
		ret = ft_add_line(ret, new);
		return (ret);
	}
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

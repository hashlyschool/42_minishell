/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:24:22 by hashly            #+#    #+#             */
/*   Updated: 2022/02/06 00:47:08 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_end_str(char *str)
{
	char	**split_start;
	char	**split_end;
	char	*ret;
	size_t	i;

	split_start = ft_split_2(str, START_VALUE);
	if ((ft_len_str_str(split_start) == 0 || split_start[1] == NULL) && \
	ft_strlen(split_start[0]) == ft_strlen(str) && \
	ft_strncmp(split_start[0], str, ft_strlen(str)) == 0)
	{
		ft_free_str_of_str(&split_start);
		return (NULL);
	}
	i = 0;
	while (split_start[i])
	{
		split_end = ft_split_2(split_start[i], END_VALUE);
		if (!ret)
			ret = ft_strdup(ft_getenv(split_end[0]));
		else
			ret = ft_strjoin_free_s1(ret, ft_getenv(split_end[0]));
		if (split_end[1])
			ret = ft_strjoin_free_s1(ret, split_end[1]);
		ft_free_str_of_str(&split_end);
		i++;
	}
	ft_free_str_of_str(&split_start);
	return (ret);
}

static char	**split_cmd_line(char **end_str)
{
	char	**ret;

	ret = ft_split(*end_str, ' ');
	free(*end_str);
	return (ret);
}

static void	get_new_cmd_line(char ***cmd_line, char *str)
{
	char	*end_str;
	char	**arr;
	size_t	i;

	end_str = get_end_str(str); //+
	if (!end_str)
	{
		*cmd_line = ft_add_line(*cmd_line, str);
		return ;
	}
	arr = split_cmd_line(&end_str); //- MASHA
	i = 0;
	while (arr[i])
		*cmd_line = ft_add_line(*cmd_line, arr[i++]); //+
	ft_free_str_of_str(&arr); //+
}

static void	replace_data_in_node(char ***arr, t_node *node)
{
	size_t	i;
	char	**temp;

	i = 0;
	temp = *arr;
	free(node->data->cmd);
	if (node->data->argv)
		ft_free_str_of_str(&(node->data->argv));
	if (temp && temp[i])
		node->data->cmd = ft_strdup(temp[i++]);
	while (temp[i])
	{
		ft_add_argv(node, temp[i]);
		i++;
	}
}

void	preparsing(t_node *node)
{
	char	*str;
	size_t	i;
	char	**cmd_line;

	cmd_line = NULL;
	get_new_cmd_line(&cmd_line, node->data->cmd); //+-
	i = 0;
	if (node->data->argv)
	{
		str = node->data->argv[i++];
		while (str)
		{
			get_new_cmd_line(&cmd_line, str); //+-
			str = node->data->argv[i++];
		}
	}
	replace_data_in_node(&cmd_line, node); //+
	free_cmd_line(&cmd_line); //+
}

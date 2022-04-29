/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:24:22 by hashly            #+#    #+#             */
/*   Updated: 2022/04/29 14:49:53 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_ret_2(char *str, char *ret, t_node *node, int *has_env_var)
{
	char	**split_end;

	split_end = ft_split_2(str, END_VALUE);
	if (!ret)
		get_ret_no_ret(split_end, &ret, node, has_env_var);
	else
		get_ret_yes_ret(split_end, &ret, node, has_env_var);
	if (split_end[1])
	{
		if (ft_strncmp(ret, START_DOUBLE_QUOTE, \
		ft_strlen(START_DOUBLE_QUOTE)) == 0 && \
		ft_strncmp(split_end[1], END_DOUBLE_QUOTE, \
		ft_strlen(END_DOUBLE_QUOTE)) == 0 && \
		*has_env_var == 0)
			ret = ft_strjoin_free_s1(ret, " ");
		ret = ft_strjoin_free_s1(ret, split_end[1]);
	}
	if (node->stop)
	{
		ft_putstr_fd("minishell: ${", STD_ERR);
		ft_putstr_fd(split_end[0], STD_ERR);
		ft_set_ret(1, "}: bad substitution\n", *node->env);
	}
	ft_free_str_of_str(&split_end);
	return (ret);
}

static char	*get_ret(char **split_start, int i, t_node *node)
{
	char	*ret;
	int		has_env_var;

	ret = NULL;
	has_env_var = 0;
	while (split_start[i])
	{
		if (ft_strnstr(split_start[i], END_VALUE, \
		ft_strlen(split_start[i])) == NULL)
		{
			if (!ret)
				ret = ft_strdup(split_start[i]);
			else
				ret = ft_strjoin_free_s1(ret, split_start[i]);
		}
		else
			ret = get_ret_2(split_start[i], ret, node, &has_env_var);
		if (node->stop)
			break ;
		i++;
	}
	return (ret);
}

char	*get_end_str(char *str, t_node *node)
{
	char	**split_start;
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
	ret = get_ret(split_start, i, node);
	ft_free_str_of_str(&split_start);
	return (ret);
}

static void	get_new_cmd_line(char ***cmd_line, char *str, t_node *node)
{
	char	*end_str;
	char	**arr;
	size_t	i;

	end_str = get_end_str(str, node);
	if (node->stop)
	{
		if (end_str)
			free(end_str);
		return ;
	}
	if (!end_str)
	{
		*cmd_line = ft_add_line(*cmd_line, str);
		return ;
	}
	arr = split_cmd_line(&end_str);
	i = 0;
	while (arr[i])
		*cmd_line = ft_add_line(*cmd_line, arr[i++]);
	ft_free_str_of_str(&arr);
}

void	preparsing(t_node *node)
{
	char	*str;
	size_t	i;
	char	**arr;

	arr = NULL;
	get_new_cmd_line(&arr, node->data->cmd, node);
	i = 0;
	if (node->data->argv && node->stop == 0)
	{
		str = node->data->argv[i++];
		while (str && node->stop == 0)
		{
			get_new_cmd_line(&arr, str, node);
			str = node->data->argv[i++];
		}
	}
	if (arr)
		replace_data_in_node(&arr, node);
	if (node->stop)
		return ;
	arr = open_star(node);
	ft_free_str_of_str(&node->data->argv);
	node->data->argv = arr;
}

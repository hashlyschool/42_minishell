/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:24:22 by hashly            #+#    #+#             */
/*   Updated: 2022/02/14 16:23:37 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_ret_2(char **split_start, char *ret, int i, char **env)
{
	char	**split_end;

	split_end = ft_split_2(split_start[i], END_VALUE);
	if (!ret)
	{
		if (split_end && split_end[0] && \
		split_end[0][0] == '?' && split_end[0][1] == 0)
			ret = ft_strdup(ft_get_status(env));
		else
			ret = ft_strdup(ft_getenv(split_end[0], env));
	}
	else
	{
		if (split_end && split_end[0] && \
		split_end[0][0] == '?' && split_end[0][1] == 0)
			ret = ft_strjoin_free_s1(ret, ft_get_status(env));
		else
			ret = ft_strjoin_free_s1(ret, ft_getenv(split_end[0], env));
	}
	if (split_end[1])
		ret = ft_strjoin_free_s1(ret, split_end[1]);
	ft_free_str_of_str(&split_end);
	return (ret);
}

static char	*get_ret(char **split_start, int i, char **env)
{
	char	*ret;

	ret = NULL;
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
			ret = get_ret_2(split_start, ret, i, env);
		i++;
	}
	return (ret);
}

static char	*get_end_str(char *str, char **env)
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
	ret = get_ret(split_start, i, env);
	ft_free_str_of_str(&split_start);
	return (ret);
}

static void	get_new_cmd_line(char ***cmd_line, char *str, char **env)
{
	char	*end_str;
	char	**arr;
	size_t	i;

	end_str = get_end_str(str, env);
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

/*
Функция, которая раскрывает переменные окружения в узле дерева
и преписывает узел
*/
void	preparsing(t_node *node)
{
	char	*str;
	size_t	i;
	char	**cmd_line;

	cmd_line = NULL;
	get_new_cmd_line(&cmd_line, node->data->cmd, node->env);
	i = 0;
	if (node->data->argv)
	{
		str = node->data->argv[i++];
		while (str)
		{
			get_new_cmd_line(&cmd_line, str, node->env);
			str = node->data->argv[i++];
		}
	}
	replace_data_in_node(&cmd_line, node);
	free_cmd_line(&cmd_line);
}

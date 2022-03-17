/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:24:22 by hashly            #+#    #+#             */
/*   Updated: 2022/03/17 17:54:03 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_error_in_name(char *name, char *flag)
{
	int	i;

	*flag = 0;
	i = 0;
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

/*
Нужно сделать проверку на валидность имени переменной окружения

minishell: ${"USER"}: bad substitution
return (1);
*/
static char	*get_ret_2(char **split_start, char *ret, int i, char **env)
{
	char	**split_end;
	char	flag;

	flag = 0;
	split_end = ft_split_2(split_start[i], END_VALUE);
	if (!ret)
	{
		if (split_end && split_end[0] && \
		split_end[0][0] == '?' && split_end[0][1] == 0)
			ret = ft_strdup(ft_get_status(env));
		else if (check_error_in_name(split_end[0], &flag) == 0)
			ret = ft_strdup(ft_getenv(split_end[0], env));
	}
	else
	{
		if (split_end && split_end[0] && \
		split_end[0][0] == '?' && split_end[0][1] == 0)
			ret = ft_strjoin_free_s1(ret, ft_get_status(env));
		else if (check_error_in_name(split_end[0], &flag) == 0)
			ret = ft_strjoin_free_s1(ret, ft_getenv(split_end[0], env));
	}
	if (split_end[1])
		ret = ft_strjoin_free_s1(ret, split_end[1]);
	ft_free_str_of_str(&split_end);
	if (flag)
		ft_set_ret(1, "minishell: ${\"USER\"}: bad substitution\n", env);
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
		if (ft_atoi(ft_get_status(env)))
			break ;
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
	if (ft_atoi(ft_get_status(env)))
		return ;
	if (!end_str)
	{
		*cmd_line = ft_add_line(*cmd_line, str);
		return ;
	}
	arr = split_cmd_line(&end_str); //-
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
	char	**arr;

	arr = NULL;
	get_new_cmd_line(&arr, node->data->cmd, node->env);
	i = 0;
	if (node->data->argv)
	{
		str = node->data->argv[i++];
		while (str && ft_atoi(ft_get_status(node->env)) == 0)
		{
			get_new_cmd_line(&arr, str, node->env);
			str = node->data->argv[i++];
		}
	}
	if (ft_atoi(ft_get_status(node->env)) != 0)
		return ;
	replace_data_in_node(&arr, node);
	free_cmd_line(&arr);
	arr = open_star(node);
	ft_free_str_of_str(&node->data->argv);
	node->data->argv = arr;
}

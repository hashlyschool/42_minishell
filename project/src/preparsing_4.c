/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:48:59 by hashly            #+#    #+#             */
/*   Updated: 2022/04/27 16:27:52 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	matching_1(char **split_arr, int *i, char **ptr, char *d_name)
{
	*ptr = d_name;
	*i = 0;
	if (ft_strncmp(split_arr[*i], STAR, ft_strlen(STAR) + 1) == 0)
	{
		(*i)++;
		while (**ptr && split_arr[*i] && **ptr != split_arr[*i][0])
			(*ptr)++;
	}
	else
	{
		*ptr = ft_strnstr(*ptr, split_arr[*i], ft_strlen(split_arr[*i]));
		if (!(*ptr))
			return (1);
		*ptr += ft_strlen(split_arr[(*i)++]);
	}
	return (0);
}

char	matching(char **arr, char *d_name)
{
	int		i;
	char	*ptr;

	if (d_name[0] == '.')
		return (0);
	if (matching_1(arr, &i, &ptr, d_name))
		return (0);
	while (arr[i] && \
	ft_strncmp(arr[i], STAR, ft_strlen(STAR) + 1) != 0)
	{
		ptr = ft_strnstr(ptr, arr[i], ft_strlen(ptr));
		if (!ptr)
			return (0);
		ptr += ft_strlen(arr[i]);
		i++;
	}
	if (!arr[i] && ft_strncmp(arr[i - 1], STAR, ft_strlen(STAR) + 1) != 0)
	{
		while (ft_strncmp(arr[i - 1], ptr, ft_strlen(arr[i - 1])) == 0)
			ptr += ft_strlen(arr[i - 1]);
		if (*ptr == 0)
			return (1);
		return (0);
	}
	return (1);
}

void	get_ret_no_ret(char **split_end, char **ret, t_node *node, int *x)
{
	char	*temp;

	if (split_end && split_end[0] && \
	split_end[0][0] == '?' && split_end[0][1] == 0)
		*ret = ft_strdup(ft_get_status(*node->env));
	else if (ft_strlen(split_end[0]) == 1 && ft_isdigit(split_end[0][0]))
	{
		if (split_end[0][0] == '0')
			*ret = ft_strdup("minishell");
		else
			*ret = ft_strdup("");
	}
	else if (check_error_in_env_name(split_end[0], &node->stop) == 0)
	{
		temp = ft_getenv(split_end[0], *node->env);
		if (temp)
			*x = 1;
		*ret = ft_strdup(temp);
	}
}

void	get_ret_yes_ret(char **split_end, char **ret, t_node *node, int *x)
{
	char	*temp;

	if (split_end && split_end[0] && \
	split_end[0][0] == '?' && split_end[0][1] == 0)
		*ret = ft_strjoin_free_s1(*ret, ft_get_status(*node->env));
	else if (check_error_in_env_name(split_end[0], &node->stop) == 0)
	{
		temp = ft_getenv(split_end[0], *node->env);
		if (temp)
			*x = 1;
		*ret = ft_strjoin_free_s1(*ret, temp);
	}
}

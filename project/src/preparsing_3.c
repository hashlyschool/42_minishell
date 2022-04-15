/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 23:16:48 by hashly            #+#    #+#             */
/*   Updated: 2022/04/15 14:26:16 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	find_file_in_dir(char ***arr, char **split_arr)
{
	char			*str;
	DIR				*dir;
	struct dirent	*dirent;
	char			find;

	find = 0;
	str = getcwd(NULL, 1024);
	dir = opendir(str);
	free(str);
	dirent = readdir(dir);
	while (dirent)
	{
		if (matching(split_arr, dirent->d_name))
		{
			*arr = ft_add_line(*arr, dirent->d_name);
			find = 1;
		}
		dirent = readdir(dir);
	}
	closedir(dir);
	return (find);
}

static void	add_star(char *str, char ***split_arr)
{
	size_t	len_str;
	size_t	len_star;

	len_str = ft_strlen(str);
	len_star = ft_strlen(STAR);
	if (ft_strncmp(str, STAR, len_star) == 0)
		*split_arr = ft_add_line_front(*split_arr, STAR);
	if (len_str > len_star && \
	ft_strncmp(str + len_str - len_star, STAR, len_star) == 0)
		*split_arr = ft_add_line(*split_arr, STAR);
}

static void	add_line_no_star(char ***ret, char *str, size_t len_star)
{
	char	*str_2;
	size_t	i;

	i = 0;
	str_2 = NULL;
	while (str[i])
	{
		if (ft_strncmp(str + i, STAR, len_star) == 0)
		{
			str_2 = ft_strjoin_free_s1(str_2, "*");
			i += len_star;
		}
		else
		{
			str_2 = ft_charjoin_libft_free_s1(str_2, str[i]);
			i++;
		}
	}
	*ret = ft_add_line(*ret, str_2);
	free(str_2);
}

static void	get_ret_add_line(t_node *node, char ***ret, int i, char *str_zero)
{
	if (ft_strncmp(node->data->argv[i], "", 1) == 0)
		*ret = ft_add_line(*ret, "");
	else
		*ret = ft_add_line(*ret, str_zero);
}

char	**open_star(t_node *node)
{
	size_t	i;
	char	**split_arr;
	char	**ret;

	i = 0;
	ret = NULL;
	while (node->data->argv && node->data->argv[i])
	{
		split_arr = ft_split_2(node->data->argv[i], STAR);
		add_star(node->data->argv[i], &split_arr);
		if (split_arr[0] == NULL || (split_arr[1] == NULL && \
		ft_strncmp(node->data->argv[i], STAR, ft_strlen(STAR) + 1) != 0))
			get_ret_add_line(node, &ret, i, split_arr[0]);
		else
		{
			if (!find_file_in_dir(&ret, split_arr))
				add_line_no_star(&ret, node->data->argv[i], ft_strlen(STAR));
		}
		ft_free_str_of_str(&split_arr);
		i++;
	}
	return (ret);
}

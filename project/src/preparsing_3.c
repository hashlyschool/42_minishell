/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 23:16:48 by hashly            #+#    #+#             */
/*   Updated: 2022/04/08 23:08:12 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
split_str - массив вида:
[ STAR ]
arg_1
arg_2
...
arg_n
[ STAR ]
проверяем имя каждого файла на совпадение с split_arr
сравнивать нужно только с не скрытыми
*/
static char	matching(char **split_arr, char *d_name)
{
	int		i;
	char	*ptr;

	if (d_name[0] == '.')
		return (0);
	i = 0;
	ptr = d_name;
	if (ft_strncmp(split_arr[i], STAR, ft_strlen(STAR) + 1) == 0)
	{
		i++;
		while (*ptr && split_arr[i] && *ptr != split_arr[i][0])
			ptr++;
	}
	else
	{
		ptr = ft_strnstr(ptr, split_arr[i], ft_strlen(split_arr[i]));
		if (!ptr)
			return (0);
		ptr += ft_strlen(split_arr[i++]);
	}
	while (split_arr[i] && \
	ft_strncmp(split_arr[i], STAR, ft_strlen(STAR) + 1) != 0)
	{
		ptr = ft_strnstr(ptr, split_arr[i], ft_strlen(ptr));
		if (!ptr)
			return (0);
		ptr += ft_strlen(split_arr[i]);
		i++;
	}
	if (!split_arr[i] && ft_strncmp(split_arr[i - 1], STAR, ft_strlen(STAR) + 1) != 0)
	{
		while (ft_strncmp(split_arr[i - 1], ptr, ft_strlen(split_arr[i - 1])) == 0)
			ptr += ft_strlen(split_arr[i - 1]);
		if (*ptr == 0)
			return (1);
		return (0);
	}
	return (1);
}

/*
проверяем имя каждого файла на совпадение с split_arr
если совпало, то нужно добавить имя этого файла в ret
возвращает 1, если совпалоо хоть одно название, иначе 0
*/
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

/*
Если в исходной строке в начале или в конце есть *, то эта функция
добавит в split_arr STAR
*/
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

static void	add_line_without_star(char ***ret, char *str, size_t len_star)
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
			str_2 = ft_charjoin_libft(str_2, str[i]);
			i++;
		}
	}
	*ret = ft_add_line(*ret, str_2);
}

/*
Эта функция проссматривает аргументы и заменяет STAR на:
- один или более аргументов, если находится файл в рабочей директории,
который совпадает по правилу раскрытия звезды
- заменяет STAR на *, если файлов не нашлось
*/
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
		{
			if (ft_strncmp(node->data->argv[i], "", 1) == 0)
				ret = ft_add_line(ret, "");
			else
				ret = ft_add_line(ret, split_arr[0]);
		}
		else
		{
			if (!find_file_in_dir(&ret, split_arr))
				add_line_without_star(&ret, node->data->argv[i], ft_strlen(STAR)); //-
		}
		ft_free_str_of_str(&split_arr);
		i++;
	}
	return (ret);
}

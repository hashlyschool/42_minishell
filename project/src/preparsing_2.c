/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:10:33 by hashly            #+#    #+#             */
/*   Updated: 2022/04/15 12:50:30 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_error_in_env_name(char *name, char *flag)
{
	int	i;

	*flag = 0;
	i = 0;
	if (name && ft_isdigit(name[0]) && name[1] == 0)
		return (1);
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
	ft_free_str_of_str(arr);
}

/*
Masha
Функция должна разделить строку по правилам разделения bash,
затем очитстить указатель end_str и вернуть ret
if end_str из одних пробелов, то все ок
*/

// char	*ft_queote_dollar(char *str, char *new_str)
// {
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*finish;
// 	int		a;
// 	int		b;
// 	int		i;

// 	i = 0;
// 	tmp = NULL;
// 	a = ft_strlen(str);
// 	b = ft_strlen(new_str);
// 	tmp = ft_substr(str, 0, a - b);
// 	finish = ft_strnstr(new_str, END_DOUBLE_QUOTE, ft_strlen(new_str));
// 	c = ft_strlen(finish);
// 	if (finish != NULL)
// 		tmp2 = ft_substr(new_str, 5, b - ft_strlen(finish) - 5);
// 	tmp = ft_strjoin_free_all(tmp, tmp2);
// 	tmp = ft_strjoin_free_s1(tmp, finish + 5);
// 	// free(new_str);
// 	free(str);
// 	// free(finish);
// 	return (tmp);
// }

char	*ft_queote_dollar(char *str, char *new_str, int i)
{
	char	*tmp;
	int		a;
	int		b;

	a = ft_strlen(str);
	b = ft_strlen(new_str);
	tmp = ft_substr(str, 0, a - b);
	tmp = ft_strjoin_free_s1(tmp, new_str + 5 + i);
	free(str);
	return (tmp);
}

char	**split_cmd_line(char **end_str)
{
	char	**ret;
	char	*new_str;
	int		i;

	i = 0;
	ret = NULL;
	new_str = ft_strnstr(*end_str, START_DOUBLE_QUOTE, ft_strlen(*end_str));
	while (new_str != NULL)
	{
		*end_str = ft_queote_dollar(*end_str, new_str, 0);
		new_str = ft_strnstr(*end_str, START_DOUBLE_QUOTE, ft_strlen(*end_str));
	}
	new_str = ft_strnstr(*end_str, END_DOUBLE_QUOTE, ft_strlen(*end_str));
	while (new_str != NULL)
	{
		*end_str = ft_queote_dollar(*end_str, new_str, 1);
		new_str = ft_strnstr(*end_str, END_DOUBLE_QUOTE, ft_strlen(*end_str));
	}
	if (new_str != NULL)
	{
		// new = ft_strjoin_free_all(left, right);
		ret = ft_add_line(ret, *end_str);
		// free(*end_str);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 19:10:33 by hashly            #+#    #+#             */
/*   Updated: 2022/04/27 02:48:10 by sstyx            ###   ########.fr       */
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

// char **ft_join_mass(char **mass1, char *end_str)
// {
// 	char **mass2;
// 	char **mass3;
// 	int i;

// 	mass3 = NULL;
// 	mass2 = ft_minishell_split(end_str);
// 	i = 0;
// 	while (mass1 && mass1[i])
// 	{
// 		mass3 = ft_add_line(mass3, mass1[i]);
// 		free(mass1[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (mass2 && mass2[i])
// 	{
// 		mass3 = ft_add_line(mass3, mass2[i]);
// 		free(mass2[i]);
// 		i++;
// 	}
// 	// mass3 = ft_add_line(mass3, end_str);
// 	free(mass1);
// 	free(mass2);
// 	return (mass3);
// }

// char **mass(char *end_str, char **ret, t_main *m, int fre)
// {
// 	int i;

// 	i = 0;
// 	if (end_str == NULL)
// 		return(ret);
// 	while (end_str[i] == '\t' || end_str[i] == '\n' || end_str[i] == '\v' \
// 		|| end_str[i] == '\f' || end_str[i] == '\r' || end_str[i] == ' ')
// 	 	i++;
// 	if (end_str[i] == 0)
// 		//ret = ft_add_line(ret, "");
// 		;
// 	else
// 		ret = ft_join_mass(ret, end_str);
// 	if (m->str2 && fre != 1)
// 		free(m->str2);
// 	return (ret);
// }

// char	*start_double(t_main *m, char *end_str, char *new_str, int n)
// {
// 	char *str1;
// 	char *str2;
// 	int		i;

// 	i = 0;
// 	if (n > 0)
// 		i = 1;
// 	str1 = NULL;
// 	str1 = ft_substr(end_str, n, new_str - end_str - n);
// 	if (str1[0] != '\0')
// 		m->m = mass(str1, m->m, m, 1);
// 	str2 = ft_strdup(end_str + ft_strlen(str1) + 5 + n);
// 	free(str1);
// 	return (str2);
// }

// char	*end_double(t_main *m, char *str2, char *new_str2, int n)
// {
// 	char *str1;

// 	str1 = NULL;
// 	str1 = ft_substr(str2, n , new_str2 - str2 - n);
// 	if (str1[0] != '\0')
// 		m->m = ft_add_line(m->m, str1);
// 	str2 = ft_strdup(new_str2);
// 	free(str1);
// 	return (str2);
// }

// char **req_dollar2(char *end_str, t_main *m)
// {
// 	m->new_str = ft_strnstr(end_str, START_DOUBLE_QUOTE, ft_strlen(end_str));
// 	m->new_str2 = ft_strnstr(end_str, END_DOUBLE_QUOTE, ft_strlen(end_str));
// 	if (m->new_str2 > m->new_str && m->new_str != 0)
// 	{
// 		m->str1 = start_double(m, end_str, m->new_str, 0);
// 		m->new_str = ft_strnstr(m->str1, END_DOUBLE_QUOTE, ft_strlen(end_str));
// 		if (m->new_str != NULL)
// 			m->str2 = end_double(m, m->str1, m->new_str, 0);
// 		else
// 			m->str2 = ft_strdup(m->str1 + 6);
// 	}
// 	else 
// 	{
// 		m->str1 = end_double(m, end_str, m->new_str2, 0);
// 		m->new_str = ft_strnstr(m->str1, START_DOUBLE_QUOTE, ft_strlen(end_str));
// 		if (m->new_str != NULL)
// 			m->str2 = start_double(m, m->str1, m->new_str, 5);
// 		else
// 			m->str2 = ft_strdup(m->str1 + 6);
// 	}
// 	if (end_str)
// 		free(end_str);
// 	free(m->str1);
// 	if (m->str2 != NULL && (ft_strnstr(m->str2, START_DOUBLE_QUOTE, ft_strlen(m->str2)) 
// 		|| ft_strnstr(m->str2, END_DOUBLE_QUOTE, ft_strlen(m->str2))))
// 		return (req_dollar2(m->str2, m));
// 	return mass(m->str2, m->m, m, 0);
// }

// char	**req_dollar(char *end_str, char **ret)
// {
// 	t_main m;

// 	m.str1 = NULL;
// 	m.str2 = NULL;
// 	m.m = ret;
// 	return (req_dollar2(end_str, &m));
// }

char	**split_cmd_line(char **end_str)
{
	char	**ret;
	char	*new_str;
	int		i;
	int		end;

	i = 0;
	end = 0;
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
		end = 1;
	}
	if (end == 1)
	{
		ret = ft_add_line(ret, *end_str);
		free(*end_str);
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
	// return (req_dollar(*end_str, ret));
}

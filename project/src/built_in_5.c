/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:41:23 by hashly            #+#    #+#             */
/*   Updated: 2022/04/14 17:10:49 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**ft_add_line_for_export(char **arg, char *line, char **key)
{
	int		i;
	char	**ret;

	i = 0;
	while (key && key[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1));
	ret[i] = NULL;
	if (line)
		ret[i - 1] = ft_strdup(line);
	else
		ret[i - 1] = NULL;
	i = i - 2;
	while (i >= 0 && arg)
	{
		ret[i] = arg[i];
		i--;
	}
	if (arg)
		free(arg);
	return (ret);
}

static void	fill_val_key(char *argv_i, size_t j, char ***key, char ***value)
{
	char	*temp;

	temp = ft_substr(argv_i, 0, j);
	*key = ft_add_line(*key, temp);
	free(temp);
	temp = ft_strdup(argv_i + (j + 1));
	*value = ft_add_line_for_export(*value, temp, *key);
	free(temp);
}

static char	*fill_key(char *arg_i, size_t j, char ***key, char **env)
{
	char	*temp;
	char	*temp_name;

	temp = ft_substr(arg_i, 0, j - 1);
	*key = ft_add_line(*key, temp);
	temp_name = ft_getenv(temp, env);
	free(temp);
	return (temp_name);
}

static void	fill_value(char *argv_i, char *temp_name, char ***key, char ***val)
{
	char	*temp;

	temp = ft_strjoin(temp_name, argv_i);
	*val = ft_add_line_for_export(*val, temp, *key);
	free(temp);
}

void	ft_parsing_argv_2(char **argv, char ***key, char ***value, char **env)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (argv && argv[i])
	{
		j = 0;
		while (argv[i][j] && argv[i][j] != '=')
			j++;
		if (argv[i][j] == 0)
		{
			*key = ft_add_line(*key, argv[i]);
			*value = ft_add_line_for_export(*value, NULL, *key);
		}
		else
		{
			if (j && argv[i][j - 1] == '+')
				fill_value(argv[i] + j + 1, \
				fill_key(argv[i], j, key, env), key, value);
			else
				fill_val_key(argv[i], j, key, value);
		}
		i++;
	}
}

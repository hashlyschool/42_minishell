/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 01:30:04 by hashly            #+#    #+#             */
/*   Updated: 2022/02/23 00:13:25 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_fill_str(char *s1, char *s2)
{
	size_t	len;
	char	*str;
	char	*ret;

	len = ft_strlen(s1) + ft_strlen(s2) + 2;
	str = (char *)malloc(sizeof(char) * len);
	ret = str;
	while (*s1)
		*str++ = *s1++;
	*str++ = '=';
	while (*s2)
		*str++ = *s2++;
	*str = 0;
	return (ret);
}

static char	**malloc_for_export(char *key, char *value, char **env)
{
	char	**ret;
	size_t	i;
	size_t	j;

	i = 0;
	while (env[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2 + 2));
	ret[i] = ft_fill_str(key, value);
	ret[i + 1] = NULL;
	ret[i + 2] = env[i + 1];
	ret[i + 3] = NULL;
	j = -1;
	i = i - 2;
	while (++j < i)
		ret[j] = env[j];
	free(env);
	return (ret);
}

static void	export_action(char *key, char *value, char **env)
{
	char	**temp_envp;
	size_t	len_key;
	size_t	i;

	i = 0;
	temp_envp = env;
	len_key = ft_strlen(key);
	while (temp_envp[i])
	{
		if (ft_strlen(temp_envp[i]) > len_key && \
		ft_strncmp(temp_envp[i], key, len_key) == 0 && \
		temp_envp[i][len_key] == '=')
		{
			free(env[i]);
			env[i] = ft_fill_str(key, value);
			return ;
		}
		i++;
	}
	env = malloc_for_export(key, value, env);
	return ;
}

static int	parsing_argv(char **argv, char ***key, char ***value)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = 0;
	while (argv && argv[i])
	{
		if (argv[i++][0] == '-')
			return (1);
	}
	i = 0;
	j = 0;
	while (argv && argv[i])
	{
		while (argv[i][j] != '=')
			j++;
		if (argv[i][j] == 0)
		{
			*key = ft_add_line(*key, argv[i]);
			*value = ft_add_line(*value, NULL);
		}
		else
		{
			temp = ft_substr(argv[i], 0, j);
			*key = ft_add_line(*key, temp);
			free(temp);
			temp = ft_strdup(argv[i] + (j + 1));
			*value = ft_add_line(*value, temp);
			free(temp);
		}
		i++;
	}
	return (0);
}

int	ft_export(char **argv, char **env)
{
	size_t	i;
	char	**key;
	char	**value;

	i = 0;
	key = NULL;
	value = NULL;
	if (parsing_argv(argv, &key, &value))
		return (ft_set_ret(1, "minishell: export: invalid argument\n", env));
	while (key[i])
	{
		if (value[i])
			export_action(key[i], value[i], env);
		i++;
	}
	i = 0;
	while (key[i])
	{
		free(key[i]);
		if (value[i++])
			free(value[i - 1]);
	}
	free(key);
	free(value);
	return (ft_set_ret(0, NULL, env));
}

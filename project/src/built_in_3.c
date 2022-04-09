/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:03:31 by hashly            #+#    #+#             */
/*   Updated: 2022/04/10 00:33:16 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	malloc_for_unset(size_t index, char ***env)
{
	char	**ret;
	size_t	i;
	size_t	j;

	i = 0;
	ret = *env;
	while (ret[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 2));
	ret[i - 1] = NULL;
	ret[i] = env[0][i + 1];
	ret[i + 1] = NULL;
	i = 0;
	j = 0;
	while (env[0][i])
	{
		if (j != index)
			ret[i++] = env[0][j];
		j++;
	}
	free(env[0][index]);
	free(env[0]);
	*env = ret;
}

//unset in loop
static int	ft_unset_in_loop(char *key, char ***env)
{
	char	**temp_envp;
	size_t	len_key;
	size_t	i;
	char	temp;

	temp_envp = *env;
	if (check_error_in_env_name(key, &temp))
	{
		ft_putstr_fd(PROGRAM_NAME": unset: `" ,STD_ERR);
		ft_putstr_fd(key, STD_ERR);
		ft_set_ret(1, "': not a valid identifier\n", *env);
		return (-1);
	}
	i = 0;
	len_key = ft_strlen(key);
	while (temp_envp[i])
	{
		if (ft_strlen(temp_envp[i]) >= len_key && \
		ft_strncmp(temp_envp[i], key, len_key) == 0 && \
		(temp_envp[i][len_key] == '=' || temp_envp[i][len_key] == 0))
		{
			malloc_for_unset(i, env);
			return (0);
		}
		i++;
	}
	return (-1);
}

//unset
int	ft_unset(char **argv, char ****env)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!argv)
		return (ret);
	while (argv[i])
	{
		if (ft_unset_in_loop(argv[i++], *env))
			ret = -1;
	}
	return (ret);
}

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

//continue export
void	ft_parsing_argv_2(char **argv, char ***key, char ***value, char **env)
{
	size_t	i;
	size_t	j;
	char	*temp;
	char	*temp_name;

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
			{
				temp = ft_substr(argv[i], 0, j - 1);
				*key = ft_add_line(*key, temp);
				temp_name = ft_getenv(temp, env);
				free(temp);
				temp = ft_strjoin(temp_name, argv[i] + (j + 1));
				*value = ft_add_line_for_export(*value, temp, *key);
				free(temp);
			}
			else
			{
				temp = ft_substr(argv[i], 0, j);
				*key = ft_add_line(*key, temp);
				free(temp);
				temp = ft_strdup(argv[i] + (j + 1));
				*value = ft_add_line_for_export(*value, temp, *key);
				free(temp);
			}
		}
		i++;
	}
}

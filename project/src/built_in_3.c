/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:03:31 by hashly            #+#    #+#             */
/*   Updated: 2022/04/14 16:41:13 by hashly           ###   ########.fr       */
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

static int	ft_unset_in_loop(char *key, char ***env, size_t	len_key)
{
	char	**temp_envp;
	size_t	i;
	char	temp;

	temp_envp = *env;
	if (check_error_in_env_name(key, &temp))
	{
		ft_putstr_fd(PROGRAM_NAME": unset: `", STD_ERR);
		ft_putstr_fd(key, STD_ERR);
		ft_set_ret(1, "': not a valid identifier\n", *env);
		return (-1);
	}
	i = 0;
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

int	ft_unset(char **argv, char ****env)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	if (!argv)
		return (ret);
	while (argv[++i])
	{
		if (ft_unset_in_loop(argv[i], *env, ft_strlen(argv[i])))
			ret = -1;
	}
	return (ret);
}

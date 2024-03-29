/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:05:33 by hashly            #+#    #+#             */
/*   Updated: 2022/04/15 10:11:29 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	***ft_copy_env(char **env)
{
	int		i;
	char	*temp;
	char	***ret;

	i = 0;
	while (env[i])
		i++;
	ret = (char ***)malloc(sizeof(char **) * (1));
	ret[0] = (char **)malloc(sizeof(char *) * (i + 1 + 2));
	ret[0][i] = NULL;
	ret[0][i + 1] = ft_strdup("0");
	ret[0][i + 2] = NULL;
	while (i)
	{
		temp = env[i - 1];
		ret[0][i - 1] = ft_strdup(temp);
		i--;
	}
	return (ret);
}

int	ft_free_envp(char ****env)
{
	size_t	i;
	char	***temp;

	i = 0;
	temp = *env;
	while (temp[0][i])
		free(temp[0][i++]);
	i++;
	free(temp[0][i]);
	free(temp[0]);
	free(temp);
	return (0);
}

int	ft_set_ret(int value, char *msg, char **env)
{
	size_t	i;

	errno = 0;
	i = 0;
	while (env[i])
		i++;
	free(env[i + 1]);
	value = (char)value;
	env[i + 1] = ft_itoa(value);
	if (msg)
	{
		if (value)
			ft_putstr_fd(msg, STD_ERR);
		else
			ft_putstr_fd(msg, STD_OUT);
	}
	return (value);
}

char	*ft_get_status(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	i++;
	return (env[i]);
}

char	*ft_getenv(char *name, char **env)
{
	char	*temp;
	size_t	name_len;
	size_t	i;

	i = 0;
	if (!env)
		return (NULL);
	temp = env[i];
	name_len = ft_strlen(name);
	while (temp)
	{
		if (ft_strlen(temp) > name_len && \
		ft_strncmp(temp, name, name_len) == 0 && \
		temp[name_len] == '=')
			return (temp + name_len + 1);
		temp = env[++i];
	}
	return (NULL);
}

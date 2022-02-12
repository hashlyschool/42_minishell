/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:05:33 by hashly            #+#    #+#             */
/*   Updated: 2022/02/12 20:54:03 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
Функция, которая принимает указатель на дефолтный список окружения
и создает на его основе массив строк следующей структуры:
str 1
str 2
...
str i
NULL
Код окончания последней программы верхнего уровня
NULL
*/
char	**ft_copy_env(char **envp)
{
	size_t	i;
	char	**ret;

	i = 0;
	while (envp[i])
		i++;
	ret = (char **)malloc(sizeof(char *) * (i + 1 + 2));
	ret[i] = NULL;
	ret[i + 1] = ft_strdup("0");
	ret[i + 2] = NULL;
	while (--i > 0)
		ret[i] = ft_strdup(envp[i]);
	ret[i] = ft_strdup(envp[i]);
	return (ret);
}

/*
Функция для очистки глобального массива кастомного окружения.
*/
int	ft_free_envp(void)
{
	size_t	i;

	i = 0;
	while (g_envp[i])
		free(g_envp[i++]);
	i++;
	free(g_envp[i]);
	free(g_envp);
	return (0);
}

/*
Функция для установки статуса завершения последней операции
*/
int	ft_set_ret(int value, char *msg)
{
	size_t	i;

	i = 0;
	while (g_envp[i])
		i++;
	free(g_envp[i + 1]);
	g_envp[i + 1] = ft_itoa(value);
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (0);
}

/*
Функция для получения статуса последней операции
*/
int	ft_get_status(void)
{
	size_t	i;

	i = 0;
	while (g_envp[i])
		i++;
	i++;
	return (ft_atoi(g_envp[i]));
}

/*
Функция для получения содержимого переменной окружения по ключу
*/
char	*ft_getenv(char *name)
{
	char	*temp;
	size_t	name_len;
	size_t	i;

	i = 0;
	if (!g_envp)
		return (NULL);
	temp = g_envp[i];
	name_len = ft_strlen(name);
	while (temp)
	{
		if (ft_strlen(temp) > name_len && \
		ft_strncmp(temp, name, name_len) == 0 && \
		temp[name_len] == '=')
			return (temp + name_len + 1);
		temp = g_envp[++i];
	}
	return (NULL);
}

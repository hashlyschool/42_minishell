/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a79856 <a79856@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:43:21 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/04 20:17:51 by a79856           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	ft_find_q_word(char const *s)
{
	size_t	q_word;

	q_word = 0;
	while ((*s == ' ' || *s == '\t' || *s == '\n'
			|| *s == '\r' || *s == '\v') && *s)
		s++;
	while (*s)
	{
		q_word++;
		while ((*s != ' ' && *s != '\t' && *s != '\n'
				&& *s != '\r' && *s != '\v') && *s)
			s++;
		while ((*s == ' ' || *s == '\t' || *s == '\n'
				|| *s == '\r' || *s == '\v') && *s)
			s++;
	}
	return (q_word);
}

static void	ft_free_mem(char **ptr, size_t len)
{
	while (len--)
		free(*ptr++);
	free(ptr);
	return ;
}

static size_t	ft_strlenc(char const *s)
{
	size_t	len;

	len = 0;
	while ((*s != ' ' && *s != '\t' && *s != '\n'
			&& *s != '\r' && *s != '\v') && *s++)
		len++;
	return (len);
}

static char	*ft_skip_c(char const *s)
{
	while ((*s == ' ' || *s == '\t' || *s == '\n'
			|| *s == '\r' || *s == '\v') && *s)
		s++;
	return ((char *)s);
}

char	**ft_minishell_split(char const *s)
{
	char	**ptr;
	size_t	q_word;
	size_t	i;
	char	*start;
	size_t	len;

	if (!s)
		return (NULL);
	i = 0;
	q_word = ft_find_q_word(s);
	ptr = (char **)malloc(sizeof(char *) * (q_word + 1));
	if (!ptr)
		return (NULL);
	start = (char *)s;
	while (q_word--)
	{
		start = ft_skip_c(start);
		len = ft_strlenc(start);
		ptr[i] = ft_substr(s, start - s, len);
		if (!ptr[i++])
			ft_free_mem(ptr, q_word);
		start = start + len;
	}
	ptr[i] = NULL;
	return (ptr);
}

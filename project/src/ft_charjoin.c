/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 23:20:07 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/26 23:20:45 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* функция для посимвольного добаления в строку*/
char	*ft_charjoin(char *str, char c)
{
	char	*ptr;
	size_t	len;
	char	*tmp;

	if (!c)
		return (NULL);
	if (!str)
	{
		str = (char *)malloc(sizeof(char *) + 1);
		str[0] = c;
		str[1] = '\0';
		return (str);
	}
	len = ft_strlen(str) + 1;
	ptr = (char *)malloc(sizeof(*str) * (len + 1));
	if (!ptr)
		return (NULL);
	tmp = str;
	while (*str)
		*ptr++ = *str++;
	*ptr++ = c;
	*ptr = 0;
	free(tmp);
	return (ptr - len);
}

char	*ft_charjoin_no_free(char *str, char c)
{
	char	*ptr;
	size_t	len;

	if (!c)
		return (NULL);
	if (!str)
	{
		str = (char *)malloc(sizeof(char *) + 1);
		str[0] = c;
		str[1] = '\0';
		return (str);
	}
	len = ft_strlen(str) + 1;
	ptr = (char *)malloc(sizeof(*str) * (len + 1));
	if (!ptr)
		return (NULL);
	while (*str)
		*ptr++ = *str++;
	*ptr++ = c;
	*ptr = 0;
	return (ptr - len);
}

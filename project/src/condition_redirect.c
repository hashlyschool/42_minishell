/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 12:32:49 by hashly            #+#    #+#             */
/*   Updated: 2022/04/15 10:11:04 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	str_is_redir(char **str, int index, char *type_redir)
{
	char	*ret;
	size_t	len_redir;
	size_t	i;

	i = 0;
	ret = NULL;
	len_redir = ft_strlen(type_redir);
	if (ft_strlen(str[index]) < len_redir + 1)
		return (0);
	while (ft_isdigit(str[index][i]))
		ret = ft_charjoin_libft_free_s1(ret, str[index][i++]);
	if (ft_strncmp(str[index] + i, type_redir, len_redir) != 0)
	{
		free(ret);
		return (0);
	}
	ret = ft_strjoin_free_s1(ret, type_redir);
	i += len_redir;
	while (ft_isspace(str[index][i]))
		i++;
	ret = ft_charjoin_libft_free_s1(ret, ' ');
	ret = ft_strjoin_free_s1(ret, str[index] + i);
	free(str[index]);
	str[index] = ret;
	return (1);
}

char	str_is_redirect(char **str, int i)
{
	if (str_is_redir(str, i, REDIR_RIGHT_ONE))
		return (1);
	if (str_is_redir(str, i, REDIR_RIGHT_TWO))
		return (2);
	if (str_is_redir(str, i, REDIR_LEFT_ONE))
		return (3);
	if (str_is_redir(str, i, REDIR_LEFT_TWO))
		return (4);
	return (0);
}

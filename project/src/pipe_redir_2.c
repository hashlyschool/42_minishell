/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:21:20 by hashly            #+#    #+#             */
/*   Updated: 2022/03/20 14:33:31 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
-1	error
1	>
2	>>
3	<
4	<<
*/
static int	find_code(char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '>')
			return (2);
		return (1);
	}
	else if (str[0] == '<')
	{
		if (str[1] == '<')
			return (4);
		return (3);
	}
	return (-1);
}

static void	proc_set_redir(t_node *node, char *file_name, int code)
{
	int		fd;

	if (code == 1 || code == 2)
	{
		if (code == 1)
			fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		else
			fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		dup2(fd, 1);
	}
	else if (code == 3)
	{
		fd = open(file_name, O_RDONLY);
		dup2(fd, 0);
	}
	if (node->redir_fd[code - 1] == -1)
		node->redir_fd[code - 1] = fd;
	else
	{
		close(node->redir_fd[code - 1]);
		node->redir_fd[code - 1] = fd;
	}
}

static void	proc_heredoc(t_node *node, char *eof, char *name_file)
{
	char	*str;
	char	flag;
	int		fd;

	//Проблема обработки сигналов... если нет доступа к файлу, то сделать пайп
	fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	flag = 0;
	dup2(node->def_fd[0], 0);
	dup2(node->def_fd[1], 1);
	while (!flag)
	{
		str = readline("> ");
		if (!str)
		{
			flag = 1;
			ft_putstr_fd(PROGRAM_NAME": warning: here-document delimited by \
			end-of-file (wanted `", STD_ERR);
			ft_putstr_fd(eof, STD_ERR);
			ft_putstr_fd("')\n", STD_ERR);
		}
		else if (ft_strncmp(str, eof, ft_strlen(eof) + 1) == 0)
		{
			flag = 1;
			free(str);
		}
		else
		{
			ft_putendl_fd(str, fd);
			free(str);
		}
	}
	close(fd);
	proc_set_redir(node, name_file, 3);
}

void	ft_set_redir(t_node *node)
{
	size_t	i;
	int		code;

	i = 0;
	while (node->data->redir[i])
	{
		code = find_code(node->data->redir[i]);
		if (code == 1 || code == 2)
			proc_set_redir(node, node->data->redir[i] + code + 1, code);
		else if (code == 3)
			proc_set_redir(node, node->data->redir[i] + 2, code);
		else if (code == 4)
			proc_heredoc(node, node->data->redir[i] + 3, "/tmp/.heredoc");
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:27:57 by hashly            #+#    #+#             */
/*   Updated: 2022/04/15 14:28:35 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ret_error_and_set_code(t_node *node, char *file_name)
{
	ft_putstr_fd(PROGRAM_NAME": ", STD_ERR);
	perror(file_name);
	errno = 0;
	ft_set_ret(1, NULL, *node->env);
	node->exec = 1;
}

static void	proc_set_redir(t_node *node, t_list_redir *content)
{
	int		fd;

	if (content->type_redir == 1 || content->type_redir == 2)
	{
		if (content->type_redir == 1)
			fd = open(content->word, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
		else
			fd = open(content->word, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
		content->fd = -1;
		if (fd < 0)
			return (ret_error_and_set_code(node, content->word));
		dup2(fd, content->n);
		content->fd = fd;
	}
	else if (content->type_redir == 3)
	{
		fd = open(content->word, O_RDONLY);
		content->fd = -1;
		if (fd < 0)
			return (ret_error_and_set_code(node, content->word));
		content->fd = fd;
		dup2(fd, content->n);
	}
}

static void	proc_heredoc(t_node *node, t_list_redir *content, char *name_file)
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
			ft_putstr_fd(content->word, STD_ERR);
			ft_putstr_fd("')\n", STD_ERR);
		}
		else if (ft_strncmp(str, content->word, ft_strlen(content->word) + 1) == 0)
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
	content->type_redir = 3;
	free(content->word);
	content->word = ft_strdup(name_file);
	proc_set_redir(node, content);
}

void	ft_set_redir(t_node *node)
{
	t_list			*temp;
	t_list_redir	*content;

	temp = node->list_redir;
	while (temp)
	{
		content = temp->content;
		if (content->type_redir == 4)
			proc_heredoc(node, content, "/tmp/.heredoc");
		else
			proc_set_redir(node, content);
		temp = temp->next;
	}
}

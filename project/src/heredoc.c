/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:01:47 by hashly            #+#    #+#             */
/*   Updated: 2022/04/29 11:14:27 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	heredoc_loop(t_list_redir *content)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			ft_putstr_fd(PROGRAM_NAME": warning: here-document delimited by \
end-of-file (wanted `", STD_ERR);
			ft_putstr_fd(content->word, STD_ERR);
			ft_putstr_fd("')\n", STD_ERR);
			break ;
		}
		else if (ft_strncmp(str, content->word, \
		ft_strlen(content->word) + 1) == 0)
		{
			free(str);
			break ;
		}
		else
		{
			ft_putendl_fd(str, content->fd);
			free(str);
		}
	}
}

static void	heredoc_child(t_node *node, t_list_redir *content, char mode)
{
	dup2(node->def_fd[0], 0);
	dup2(node->def_fd[1], 1);
	signal(SIGINT, sig_int_heredoc);
	heredoc_loop(content);
	close(content->fd);
	if (mode)
		close(content->pipe_heredoc[0]);
	exit(0);
}

static char	open_temp_file(t_list_redir *content, char *name_file)
{
	content->fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	if (content->fd != -1)
		return (1);
	content->type_redir = 3;
	return (0);
}

static void	processing_mode(char mode, char *name_file, t_list_redir *content)
{
	if (mode == 0)
	{
		free(content->word);
		content->word = ft_strdup(name_file);
		content->type_redir = 3;
	}
	else
	{
		close(content->pipe_heredoc[1]);
		dup2(content->pipe_heredoc[0], content->n);
		close(content->pipe_heredoc[0]);
		content->fd = -1;
	}
}

void	proc_heredoc(t_node *node, t_list_redir *content, char *name_file)
{
	int		pid;
	char	mode;
	int		ret;

	mode = 0;
	ret = 0;
	if (open_temp_file(content, name_file) == 0)
	{
		pipe(content->pipe_heredoc);
		content->fd = content->pipe_heredoc[1];
		mode = 1;
	}
	pid = fork();
	if (pid == 0)
		heredoc_child(node, content, mode);
	else
		waitpid(pid, &ret, 0);
	if (ret)
		node->stop = 1;
	processing_mode(mode, name_file, content);
}

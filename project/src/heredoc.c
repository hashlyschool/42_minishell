/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 17:01:47 by hashly            #+#    #+#             */
/*   Updated: 2022/04/15 17:23:51 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	heredoc_child(t_node *node, t_list_redir *content, char *name_file)
{
	char	*str;
	char	flag;
	int		fd;

	//Проблема обработки сигналов... если нет доступа к файлу, то сделать пайп
	fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	// if (!fd)
	// 	set_pipe();
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
	exit(0);
}

void	proc_heredoc(t_node *node, t_list_redir *content, char *name_file)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		heredoc_child(node, content, name_file);
	else
		waitpid(pid, NULL, 0);
	content->type_redir = 3;
	free(content->word);
	content->word = ft_strdup(name_file);
}

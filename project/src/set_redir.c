/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:27:57 by hashly            #+#    #+#             */
/*   Updated: 2022/04/29 18:28:41 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_int_heredoc(int signo)
{
	signo = 0;
	ft_putstr_fd("\n", STD_ERR);
	exit(1);
}

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
		close(fd);
	}
	else if (content->type_redir == 3)
	{
		fd = open(content->word, O_RDONLY);
		content->fd = -1;
		if (fd < 0)
			return (ret_error_and_set_code(node, content->word));
		dup2(fd, content->n);
		close(fd);
	}
}

static void	open_env_var(t_node *node, t_list_redir **content)
{
	char	*end_str;
	char	*word;
	char	**arr;

	end_str = get_end_str((*content)->word, node);
	if (!end_str || !end_str[0])
		return (free(end_str));
	arr = split_cmd_line(&end_str);
	word = ft_strdup(arr[0]);
	if (ft_len_str_str(arr) > 1)
		return (err_1(content, node, &arr, &word));
	ft_free_str_of_str(&arr);
	free((*content)->word);
	(*content)->word = word;
}

void	ft_set_redir(t_node *node)
{
	t_list			*temp;
	t_list_redir	*content;

	temp = node->list_redir;
	while (temp)
	{
		content = temp->content;
		if (content->type_redir > 0 && content->type_redir < 4)
			open_env_var(node, &content);
		if (ft_atoi(ft_get_status(*node->env)))
			return ;
		if (content->type_redir == 4)
			proc_heredoc(node, content, "/tmp/.heredoc");
		if (content->type_redir != 4)
			proc_set_redir(node, content);
		temp = temp->next;
	}
}

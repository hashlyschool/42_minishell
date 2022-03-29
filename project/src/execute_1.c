/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:52:50 by hashly            #+#    #+#             */
/*   Updated: 2022/03/29 17:24:51 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**get_argv(t_node *node)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	ret = ft_add_line(ret, node->data->cmd_exec);
	while (node->data->argv && node->data->argv[i])
	{
		ret = ft_add_line(ret, node->data->argv[i]);
		i++;
	}
	return (ret);
}

/*
Если имя команды file и если есть PATH
- сплитуем PATH по :
- ищем в каждой из директорий нужный файл или папка
	(если нет bash: ./qwerty: No such file or directory 127)
- если папка, то (bash: /bin: Is a directory, error 126)
- есть ли права на исполнение файла (если нет 126)
	(bash: ./minishell: Permission denied)
- исполняем
иначе
Если это абсолютный или относительный путь:
/dir1/dir2/file ./file /dir1/file
или если file, но нет PATH
- проверить есть ли файл или папка с таким именем
	(если нет bash: ./qwerty: No such file or directory 127)
- если папка, то (bash: /bin: Is a directory, error 126)
- есть ли права на исполнение файла (если нет 126)
	(bash: ./minishell: Permission denied)
- исполняем
*/
static void	ft_execve_node(t_node *node)
{
	pid_t	pid;
	int		ret;
	char	**argv;

	node->data->cmd_exec = ft_strdup(node->data->cmd);
	pid = fork();
	if (pid == 0)
	{
		open_path_and_check_access(node);
		argv = get_argv(node);
		execve(node->data->cmd_exec, argv, *node->env);
		ft_free_str_of_str(&argv);
		perror(node->data->cmd);
		exit(errno);
	}
	else
	{
		if (waitpid(pid, &ret, 0) == -1)
			return (perror("WAIT_PID"));
		if (WIFSIGNALED(ret))
			ft_set_ret(130, NULL, *node->env);
		else if (WIFEXITED(ret))
			ft_set_ret(WEXITSTATUS(ret), NULL, *node->env);
	}
	return ;
}

void	error_handling(int mode, t_node *node, char **path)
{
	if (path)
		ft_free_str_of_str(&path);
	if (mode == 1)
		output_error(1, node);
	if (mode == 0)
		output_error(2, node);
}

static void	execute_cmd_in_node(t_node *node)
{
	if (node->next_lvl && cond_status(node) == 0)
		execute_level(node->next_lvl);
	else if (!node->next_lvl)
	{
		if (node->exec == 1)
			return ;
		node->exec = 1;
		if (!node->data->cmd && node->exec != 1)
			node->stop = 1;
		if (node->exit == 1 || !node->data->cmd || cond_status(node))
			return ;
		preparsing(node);
		if (node->stop)
			return ;
		if (cond_is_built_in(node))
			;
		else if (node->data->cmd[0] != 0)
			ft_execve_node(node);
	}
}

static void	execute_child_node(t_node *node)
{
	execute_cmd_in_node(node);
	ft_close_redir_pipe(node);
	if (node->data->pipe == PIPE_ON_THE_LEFT)
		exit(ft_atoi(ft_get_status(*node->env)));
	exit(0);
}

static void	execute_parent_node(t_node *node, pid_t pid, t_list **pipeline)
{
	int			ret;
	t_content	*content;

	content = (t_content *)malloc(sizeof(t_content) * 1);
	content->node = node;
	content->pid = pid;
	ft_lstadd_back(pipeline, ft_lstnew(content));
	if (node->data->pipe == PIPE_ON_THE_LEFT)
	{
		while (1)
		{
			pid = waitpid(-1, &ret, 0);
			if (pid > 0)
				processing_exit_code(pipeline, pid, ret);
			if (pipilene_is_over(pipeline))
			{
				ft_lstclear(pipeline, &free);
				*pipeline = NULL;
				return ;
			}
		}
	}
}

static void	execute_node_or_pipe(t_node *node, t_list **pipeline)
{
	pid_t		pid;

	if (node->data->pipe)
	{
		if (node->data->pipe == PIPE_ON_THE_RIGHT)
			open_pipe_in_all_pipeline(node);
		ft_set_redir_pipe(node);
		pid = fork();
		if (pid == 0)
			execute_child_node(node);
		execute_parent_node(node, pid, pipeline);
	}
	else
	{
		ft_set_redir_pipe(node);
		execute_cmd_in_node(node);
		ft_close_redir_pipe(node);
	}
}

void	execute_level(t_node *node)
{
	t_list	*pipeline;

	set_default_fd(node);
	pipeline = NULL;
	while (node)
	{
		execute_node_or_pipe(node, &pipeline);
		if (node->next == NULL)
			close_default_fd(node);
		node = node->next;
	}
}

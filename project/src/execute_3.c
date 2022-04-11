/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:56:00 by hashly            #+#    #+#             */
/*   Updated: 2022/04/11 21:41:48 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_handling(int mode, t_node *node, char **path)
{
	if (path)
		ft_free_str_of_str(&path);
	if (mode == 1 || mode == -1)
		output_error(1, node);
	if (mode == 0)
		output_error(2, node);
}

static char	**get_argv(t_node *node)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	ret = ft_add_line(ret, node->data->cmd);
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
		if (errno == ENOEXEC)
			exit(0);
		ft_putstr_fd(PROGRAM_NAME": ", STD_ERR);
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

void	execute_cmd_in_node(t_node *node)
{
	pid_t	pid;
	int		ret;

	if (node->next_lvl && cond_status(node) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execute_level(node->next_lvl);
			exit(ft_atoi(ft_get_status(*node->env)));
		}
		else
		{
			waitpid(pid, &ret, 0);
			if (WIFSIGNALED(ret))
				ft_set_ret(130, NULL, *node->env);
			else if (WIFEXITED(ret))
				ft_set_ret(WEXITSTATUS(ret), NULL, *node->env);
		}
	}
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
		// ft_add_last_cmd(cmd, env);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 22:52:50 by hashly            #+#    #+#             */
/*   Updated: 2022/02/19 15:16:18 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
static void	ft_execve(t_node *node)
{
	pid_t	pid;
	int		ret;
	char	**argv;

	pid = fork();
	if (pid == 0)
	{
		open_path_and_check_access(node);
		argv = get_argv(node);
		execve(node->data->cmd, argv, node->env);
		ft_free_str_of_str(&argv);
		perror(node->data->cmd);
		exit(errno);
	}
	else
	{
		if (waitpid(pid, &ret, 0) == -1)
			return (perror("WAIT_PID"));
		if (WIFSIGNALED(ret))
			ft_set_ret(130, NULL, node->env);
		else if (WIFEXITED(ret))
			ft_set_ret(WEXITSTATUS(ret), NULL, node->env);
	}
	return ;
}

static void	action(t_node *node)
{
	node->exec = 1;
	if (cond_status(node))
		return ;
	preparsing(node);
	// open_star(node);
	if (cond_is_built_in(node))
		;
	else
		ft_execve(node);
}

/*
Функция принимает указатель на корень дерева.
В зависимости от содержимого и структуры дерева происходит
выполнение соответствующих операций
*/
void	execute(t_node *node)
{
	t_node * temp;

	while (node->exec != 1)
	{
		temp = node;
		ft_set_redir_pipe(temp);
		if (node->next_lvl && node->exec == 0)
			node = node->next_lvl;
		else if (node->next)
		{
			action(node);
			node = node->next;
		}
		else if (node->prev_lvl)
		{
			action(node);
			node = node->prev_lvl;
			node->exec = 1;
		}
		if (temp->exec == 1)
			ft_close_redir_pipe(temp);
		if (!node->prev_lvl && !node->next && node->exec == 0 && \
		node->data->cmd)
		{
			action(node);
			ft_close_redir_pipe(node);
		}
	}
}

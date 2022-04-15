/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:07:49 by hashly            #+#    #+#             */
/*   Updated: 2022/04/15 10:13:59 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	find_cmd_in_dir(t_node *node, char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			flag;
	size_t			len;
	char			*str;

	flag = 0;
	dir = opendir(path);
	if (!dir)
		return (flag);
	dirent = readdir(dir);
	str = node->data->cmd_exec;
	len = ft_strlen(str);
	while (dirent)
	{
		if (!flag && ft_strncmp(str, dirent->d_name, len + 1) == 0)
			flag = 1;
		else if (!flag && ft_strncmp(dirent->d_name, str, len - 1) == 0 \
		&& str[len - 1] == '/' && str[len] == 0)
			flag = 1;
		dirent = readdir(dir);
	}
	closedir(dir);
	return (flag);
}

static char	**ret_path_replace_cmd(t_node *node)
{
	size_t	i;
	int		end;
	char	**ret;
	char	*temp;

	end = -1;
	i = 0;
	ret = NULL;
	while (node->data->cmd_exec[i])
	{
		if (node->data->cmd_exec[i++] == '/' && node->data->cmd_exec[i])
			end = i - 1;
	}
	if (end == -1)
		return (ft_add_line(ret, "./"));
	temp = ft_substr(node->data->cmd_exec, 0, end + 1);
	ret = ft_add_line(ret, temp);
	free(temp);
	temp = ft_substr(node->data->cmd_exec, end + 1, \
	ft_strlen(node->data->cmd_exec));
	free(node->data->cmd_exec);
	node->data->cmd_exec = temp;
	return (ret);
}

static void	find_cmd(t_node *node)
{
	char	**path;
	int		i;
	char	file_find;
	int		mode;

	path = NULL;
	mode = cmd_in_path(node);
	if (mode == 1)
		path = ft_split(ft_getenv("PATH", *node->env), ':');
	else
		path = ret_path_replace_cmd(node);
	i = -1;
	file_find = 0;
	while (path && path[++i] && file_find == 0)
	{
		file_find = find_cmd_in_dir(node, path[i]);
		if (file_find)
			break ;
	}
	if (!file_find && ft_strncmp(node->data->cmd_exec, "", 1) != 0)
		error_handling(mode, node, path);
	if (mode == 1 && file_find)
		node->data->cmd_exec = ft_strjoin_free_s2("/", node->data->cmd_exec);
	node->data->cmd_exec = ft_strjoin_free_s2(path[i], node->data->cmd_exec);
	ft_free_str_of_str(&path);
}

static char	cmd_is_folder(t_node *node)
{
	DIR	*dir;

	dir = opendir(node->data->cmd_exec);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	if (errno == EACCES)
		return (1);
	return (0);
}

void	open_path_and_check_access(t_node *node)
{
	find_cmd(node);
	if (cmd_is_folder(node))
		output_error(3, node);
	else if (access(node->data->cmd_exec, F_OK))
	{
		ft_putstr_fd(PROGRAM_NAME": ", STD_ERR);
		perror(node->data->cmd);
		exit(127);
	}
	else if (access(node->data->cmd_exec, R_OK | X_OK))
	{
		ft_putstr_fd(PROGRAM_NAME": ", STD_ERR);
		perror(node->data->cmd_exec);
		exit(126);
	}
}

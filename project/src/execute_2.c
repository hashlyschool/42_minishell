/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 15:07:49 by hashly            #+#    #+#             */
/*   Updated: 2022/02/20 20:04:55 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	find_cmd_in_dir(t_node *node, char *path)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			flag;

	flag = 0;
	dir = opendir(path);
	if (!dir)
		return (flag);
	dirent = readdir(dir);
	while (dirent)
	{
		if (!flag && ft_strncmp(node->data->cmd, dirent->d_name, \
		ft_strlen(node->data->cmd) + 1) == 0)
			flag = 1;
		dirent = readdir(dir);
	}
	closedir(dir);
	return (flag);
}

static char	**ret_path_replace_cmd(t_node *node)
{
	size_t	i;
	size_t	end;
	char	**ret;
	char	*temp;

	end = 0;
	i = 0;
	ret = NULL;
	while (node->data->cmd[i])
	{
		if (node->data->cmd[i++] == '/')
			end = i - 1;
	}
	temp = ft_substr(node->data->cmd, 0, end);
	ret = ft_add_line(ret, temp);
	free(temp);
	temp = ft_substr(node->data->cmd, end + 1, ft_strlen(node->data->cmd));
	free(node->data->cmd);
	node->data->cmd = temp;
	return (ret);
}

static int	find_cmd(t_node *node)
{
	char	**path;
	int		i;
	char	file_find;

	path = NULL;
	if (cmd_in_path(node)) //+
		path = ft_split(ft_getenv("PATH", node->env), ':');
	else
		path = ret_path_replace_cmd(node); //+
	i = -1;
	file_find = 0;
	while (path[++i] && file_find == 0)
	{
		file_find = find_cmd_in_dir(node, path[i]); //+
		if (file_find)
			break ;
	}
	// if (file_find)
	// {
		node->data->cmd = ft_strjoin_free_s2("/", node->data->cmd);
		node->data->cmd = ft_strjoin_free_s2(path[i], node->data->cmd);
	// }
	ft_free_str_of_str(&path);
	return (file_find);
}

static char	cmd_is_folder(t_node *node)
{
	DIR				*dir;

	dir = opendir(node->data->cmd);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

void	open_path_and_check_access(t_node *node)
{
	int	status;

	status = find_cmd(node);
	if (status == 0) //+
		exit(ft_set_ret(127, "minishell: command not found\n", node->env)) ;
	if (cmd_is_folder(node)) //-
		exit(ft_set_ret(126, "minishell: /bin: Is a directory\n", node->env));
	if (access(node->data->cmd, X_OK))
	{
		perror(node->data->cmd);
		exit(errno);
	}
}

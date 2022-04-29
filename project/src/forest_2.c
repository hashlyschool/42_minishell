/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forest_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hashly <hashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 20:56:31 by hashly            #+#    #+#             */
/*   Updated: 2022/04/29 19:07:06 by hashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_add_redir(t_node *node, char *str, int type)
{
	t_list_redir	*content;
	char			**temp;

	content = (t_list_redir *)malloc(sizeof(t_list_redir) * 1);
	content->type_redir = type;
	if (type == 1)
		temp = ft_split_2(str, REDIR_RIGHT_ONE);
	else if (type == 2)
		temp = ft_split_2(str, REDIR_RIGHT_TWO);
	else if (type == 3)
		temp = ft_split_2(str, REDIR_LEFT_ONE);
	else
		temp = ft_split_2(str, REDIR_LEFT_TWO);
	if (temp[1] == NULL)
	{
		content->n = type <= 2;
		content->word = ft_strtrim(temp[0], "\t\n\v\f\r ");
	}
	else
	{
		content->n = ft_atoi(temp[0]);
		content->word = ft_strtrim(temp[1], "\t\n\v\f\r ");
	}
	ft_free_str_of_str(&temp);
	ft_lstadd_back(&node->list_redir, ft_lstnew(content));
}

static void	fill_node(char **str, int i, t_node *node)
{
	int	redir;

	node->exec = 0;
	redir = str_is_redirect(str, i);
	if (redir)
		ft_add_redir(node, str[i], redir);
	else if (node->data->cmd == NULL)
		node->data->cmd = ft_strdup(str[i]);
	else
		ft_add_argv(node, str[i]);
}

static char	check_error_in_cmd_line(char **line, t_node *node)
{
	char	error;

	error = 0;
	if (line || node)
		;
	if (error)
	{
		ft_set_ret(2, "bash: syntax error near unexpected token `", *node->env);
		ft_putstr_fd("token", 1);
		ft_putstr_fd("`'\n", 1);
	}
	return (error);
}

static char	def_root(t_node **temp, t_node **root, char **line, char ***env)
{
	*temp = create_empty_node(env, 0);
	(*temp)->def_fd[0] = dup(0);
	(*temp)->def_fd[1] = dup(1);
	*root = *temp;
	if (!line || check_error_in_cmd_line(line, *root))
	{
		(*root)->stop = 1;
		return (1);
	}
	return (0);
}

t_node	*get_forest(char **line, char ***env, char mode, int i)
{
	t_node	*root;
	t_node	*temp;

	if (def_root(&temp, &root, line, env) == 1)
		return (root);
	root->mode = mode;
	while (line && line[++i])
	{
		if (ft_strncmp(line[i], BR_LEFT, ft_strlen(BR_LEFT) + 1) == 0)
			temp = create_node_next_lvl(temp, env, mode);
		else if (ft_strncmp(line[i], BR_RIGHT, ft_strlen(BR_RIGHT) + 1) == 0)
			temp = go_prev_lvl(temp);
		else if (ft_strncmp(line[i], AND_STR, ft_strlen(AND_STR) + 1) == 0)
			temp = create_next_node(temp, AND, env, mode);
		else if (ft_strncmp(line[i], OR_STR, ft_strlen(OR_STR) + 1) == 0)
			temp = create_next_node(temp, OR, env, mode);
		else if (ft_strncmp(line[i], PIPE_STR, ft_strlen(PIPE_STR) + 1) == 0)
			temp = create_next_node(temp, PIPE, env, mode);
		else if (ft_strncmp(line[i], SEMICOLON, ft_strlen(SEMICOLON) + 1) == 0)
			temp = create_next_node(temp, SEMICOLON_CODE, env, mode);
		else
			fill_node(line, i, temp);
	}
	return (root);
}

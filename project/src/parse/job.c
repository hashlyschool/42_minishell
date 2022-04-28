/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:49:29 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/26 23:01:12 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_str(void *string)
{
	char	*str;

	str = (char *)string;
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	job_del(t_job *self)
{
	if (self)
	{
		if (self->argv)
		{
			free_str(self->argv);
			self->argv = NULL;
		}
		ft_lstclear(&(self->redir_in), free_str);
		ft_lstclear(&(self->redir_out), free_str);
		ft_lstclear(&(self->redir_append), free_str);
		free(self);
	}
}

t_job	*job_new(void)
{
	t_job	*job;

	job = (t_job *)malloc(sizeof(t_job));
	if (!job)
		return (NULL);
	job->cmd = NULL;
	job->argv = NULL;
	job->argc = 0;
	job->redir_in = NULL;
	job->redir_out = NULL;
	job->redir_append = NULL;
	job->del = job_del;
	return (job);
}

void	job_append_arg(t_job *self, char *arg)
{
	char	**tmp;
	size_t	i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (self->argc + 2));
	if (!tmp || !arg)
		process_syserror();
	if (self->argc == 0)
	{
		tmp[0] = arg;
		tmp[1] = NULL;
	}
	else
	{
		while (self->argv[i])
		{
			tmp[i] = self->argv[i];
			i++;
		}
		tmp[i] = arg;
		tmp[++i] = NULL;
		free(self->argv);
	}
	self->argv = tmp;
	self->argc += 1;
}

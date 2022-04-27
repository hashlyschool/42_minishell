/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_make_jobs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstyx <sstyx@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:49:59 by sstyx             #+#    #+#             */
/*   Updated: 2022/04/27 13:15:36 by sstyx            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	parser_append_job(t_parsers *self, t_job *job, size_t i)
{
	t_job	**tmp;

	i = 0;
	tmp = (t_job **)malloc(sizeof(t_job) * (self->jobs_len + 2));
	if (!tmp)
		process_syserror();
	if (self->jobs_len == 0)
	{
		tmp[0] = job;
		tmp[1] = NULL;
	}
	else
	{
		while (self->jobs[i])
		{
			tmp[i] = self->jobs[i];
			i++;
		}
		tmp[i] = job;
		tmp[++i] = NULL;
	}
	self->jobs = tmp;
	self->jobs_len += 1;
	free(tmp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_group.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:01:32 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/09 17:04:25 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	finalize_group2(t_exec *exec)
{
	exec->group[exec->idx] = exec->cmds[exec->j];
	exec->idx = exec->idx + 1;
	exec->j = exec->j + 1;
}

static void	finalize_group3(t_exec *exec)
{
	exec->group[exec->idx] = exec->outfile_name;
	exec->idx = exec->idx + 1;
}

void	finalize_group(t_exec *exec)
{
	exec->total = exec->ncmd;
	if (exec->infile_name)
		exec->total = exec->total + 1;
	if (exec->outfile_name)
		exec->total = exec->total + 1;
	exec->group = malloc((exec->total + 1) * sizeof(char *));
	if (!exec->group)
		return ;
	exec->idx = 0;
	if (exec->infile_name)
	{
		exec->group[exec->idx] = exec->infile_name;
		exec->idx = exec->idx + 1;
	}
	exec->j = 0;
	while (exec->j < exec->ncmd)
		finalize_group2(exec);
	if (exec->outfile_name)
		finalize_group3(exec);
	exec->group[exec->idx] = NULL;
	if (exec->idx == 0)
	{
		exec->group[0] = ft_strdup("0");
		exec->group[1] = NULL;
	}
}

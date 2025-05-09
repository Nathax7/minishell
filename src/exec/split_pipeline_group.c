/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline_group.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:56:23 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/09 17:05:01 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	init_exec(t_exec *exec)
{
	exec->count = 0;
	exec->i = 0;
	exec->ncmd = 0;
	exec->ng = 0;
	exec->group = NULL;
	exec->groups = NULL;
	exec->infile_name = NULL;
	exec->outfile_name = NULL;
	exec->infile = -1;
	exec->outfile = -1;
}

static char	**allocate_cmd_buffer(int count)
{
	return (ft_calloc((count + 1), sizeof(char *)));
}

static char	***allocate_groups(int count)
{
	return (ft_calloc((count + 1), sizeof(char **)));
}

void	split_pipeline_groups(t_exec *exec, char **tokens)
{
	init_exec(exec);
	while (tokens && tokens[exec->count])
		exec->count = exec->count + 1;
	exec->groups = allocate_groups(exec->count);
	if (!exec->groups)
		return ;
	exec->cmds = allocate_cmd_buffer(exec->count);
	if (!exec->cmds)
	{
		free_exec(exec, -1, NULL, NULL);
		return ;
	}
	split_groups(exec, tokens);
	if (exec->ncmd > 0 || exec->infile_name || exec->outfile_name)
	{
		finalize_group(exec);
		if (exec->group)
		{
			exec->groups[exec->ng] = exec->group;
			exec->ng = exec->ng + 1;
		}
	}
	exec->groups[exec->ng] = NULL;
	free(exec->cmds);
}

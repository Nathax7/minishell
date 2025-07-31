/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/24 15:18:08 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	close_all_pipes(t_exec *exec)
{
	int	i;

	if (!exec || !exec->pipes)
		return ;
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		if (exec->pipes[i])
		{
			safe_close(&exec->pipes[i][0]);
			safe_close(&exec->pipes[i][1]);
			free(exec->pipes[i]);
			exec->pipes[i] = NULL;
		}
		i++;
	}
	free(exec->pipes);
	exec->pipes = NULL;
}

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_pipes(t_exec *exec, int failed_index)
{
	int	j;

	j = 0;
	while (j < failed_index)
	{
		if (exec->pipes[j])
		{
			if (exec->pipes[j][0] != -1)
				safe_close(&exec->pipes[j][0]);
			if (exec->pipes[j][1] != -1)
				safe_close(&exec->pipes[j][1]);
			free(exec->pipes[j]);
		}
		j++;
	}
	free(exec->pipes);
	exec->pipes = NULL;
}

t_cmd	*free_parsing_cmd(t_cmd **head)
{
	free_cmd_list((*head), 0);
	return (NULL);
}

int	free_infile_name(t_files *files)
{
	free(files->infile_name);
	files->infile_name = NULL;
	return (1);
}

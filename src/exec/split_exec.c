/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:01:32 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 15:39:45 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	is_token(const char *tok, const char *s)
{
	return (ft_strcmp(tok, s) == 0);
}

static char	**allocate_cmd_buffer(int count)
{
	return (malloc((count + 1) * sizeof(char *)));
}

static char	***allocate_groups(int count)
{
	return (malloc((count + 1) * sizeof(char **)));
}
void init_exec(t_exec *exec)
{
	exec->count = 0;
	exec->i = 0;
	exec->ncmd = 0;
	exec->ng = 0;
	exec->infile_name = NULL;
	exec->outfile_name = NULL;
}

// void free_exec(t_exec *exec)
// {

// }

static void finalize_group(t_exec *exec)
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
	{
		exec->group[exec->idx] = exec->cmds[exec->j];
		exec->idx = exec->idx + 1;
		exec->j = exec->j + 1;
	}
	if (exec->outfile_name)
	{
		exec->group[exec->idx] = exec->outfile_name;
		exec->idx = exec->idx + 1;
	}
	exec->group[exec->idx] = NULL;
	if (exec->idx == 0)
	{
		exec->group[0] = ft_strdup("0");
		exec->group[1] = NULL;
	}
}

void	split_groups(t_exec *exec, char **tokens)
{
	while (exec->i < exec->count)
	{
		if (is_token(tokens[exec->i], "<") && exec->i + 1 < exec->count)
		{
			free(exec->infile_name);
			exec->infile_name = ft_strdup(tokens[exec->i + 1]);
			open_infile_exec(exec, exec->infile_name);
			close(exec->infile);
			exec->i = exec->i + 2;
		}
		else if (is_token(tokens[exec->i], ">") && exec->i + 1 < exec->count)
		{
			free(exec->outfile_name);
			exec->outfile_name = ft_strdup(tokens[exec->i + 1]);
			open_outfile_exec(exec, exec->outfile_name, 1);
			close(exec->outfile);
			exec->i = exec->i + 2;
			if (!(exec->i < exec->count && is_token(tokens[exec->i], ">")))
			{
				finalize_group(exec);
				if (!exec->group)
					break ;
				exec->groups[exec->ng] = exec->group;
				exec->ng = exec->ng + 1;
				exec->ncmd = 0;
				exec->infile_name = NULL;
				exec->outfile_name = NULL;
			}
		}
		else if (is_token(tokens[exec->i], "|"))
			exec->i = exec->i + 1;
		else
		{
			exec->cmds[exec->ncmd] = ft_strdup(tokens[exec->i]);
			exec->ncmd = exec->ncmd + 1;
			exec->i = exec->i + 1;
		}
	}
}

void split_pipeline_groups(t_exec *exec, char **tokens)
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
}

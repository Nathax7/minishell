/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:01:32 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/02 17:11:20 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	free_split(char **arr)
{
	char **p;

	p = arr;

	while (p && *p)
	{
		free(*p);
		p++;
	}
	free(arr);
}

void	free_triple(char ***triple)
{
	char	***p;

	p = triple;
	while (p && *p)
	{
		free_split(*p);
		p++;
	}
	free(triple);
}

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

static char	**finalize_group(t_exec *exec)
{
	exec->total = exec->ncmd;
	if (exec->infile)
		exec->total = exec->total + 1;
	if (exec->outfile)
		exec->total = exec->total + 1;
	exec->group = malloc((exec->total + 1) * sizeof(char *));
	if (!exec->group)
		return (NULL);
	exec->idx = 0;
	if (exec->infile)
	{
		exec->group[exec->idx] = exec->infile;
		exec->idx = exec->idx + 1;
	}
	exec->j = 0;
	while (exec->j < exec->ncmd)
	{
		exec->group[exec->idx] = exec->cmds[exec->j];
		exec->idx = exec->idx + 1;
		exec->j = exec->j + 1;
	}
	if (exec->outfile)
	{
		exec->group[exec->idx] = exec->outfile;
		exec->idx = exec->idx + 1;
	}
	exec->group[exec->idx] = NULL;
	if (exec->idx == 0)
	{
		exec->group[0] = ft_strdup("0");
		exec->group[1] = NULL;
	}
	return (exec->group);
}

char	***split_pipeline_groups(t_exec *exec, char **tokens)
{
	exec->count = 0;
	while (tokens && tokens[exec->count])
		exec->count = exec->count + 1;
	exec->groups = allocate_groups(exec->count);
	if (!exec->groups)
		return (NULL);
	exec->cmds = allocate_cmd_buffer(exec->count);
	if (!exec->cmds)
	{
		free(exec->groups);
		return (NULL);
	}
	exec->i = 0;
	exec->ncmd = 0;
	exec->ng = 0;
	exec->infile = NULL;
	exec->outfile = NULL;
	while (exec->i < exec->count)
	{
		if (is_token(tokens[exec->i], "<") && exec->i + 1 < exec->count)
		{
			free(exec->infile);
			exec->infile = ft_strdup(tokens[exec->i + 1]);
			exec->i = exec->i + 2;
		}
		else if (is_token(tokens[exec->i], ">") && exec->i + 1 < exec->count)
		{
			free(exec->outfile);
			exec->outfile = ft_strdup(tokens[exec->i + 1]);
			exec->i = exec->i + 2;
			if (!(exec->i < exec->count && is_token(tokens[exec->i], ">")))
			{
				exec->group = finalize_group(exec);
				if (!exec->group)
					break ;
				exec->groups[exec->ng] = exec->group;
				exec->ng = exec->ng + 1;
				exec->ncmd = 0;
				exec->infile = NULL;
				exec->outfile = NULL;
			}
		}
		else if (is_token(tokens[exec->i], "|"))
		{
			exec->i = exec->i + 1;
		}
		else
		{
			exec->cmds[exec->ncmd] = ft_strdup(tokens[exec->i]);
			exec->ncmd = exec->ncmd + 1;
			exec->i = exec->i + 1;
		}
	}
	if (exec->ncmd > 0 || exec->infile || exec->outfile)
	{
		exec->group = finalize_group(exec);
		if (exec->group)
		{
			exec->groups[exec->ng] = exec->group;
			exec->ng = exec->ng + 1;
		}
	}
	exec->groups[exec->ng] = NULL;
	free(exec->cmds);
	return (exec->groups);
}

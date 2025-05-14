/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline_group.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:56:23 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/14 15:45:10 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	init_exec(t_exec *exec)
{
	exec->count = 0;
	exec->i = 0;
	exec->ncmd = 0;
	exec->ng = 0;
	exec->redir = 0;
	exec->redir_in = 0;
	exec->redir_out = 0;
	exec->group = NULL;
	exec->groups = NULL;
	exec->infile_name = NULL;
	exec->outfile_name = NULL;
	exec->infile = -1;
	exec->outfile = -1;
}

static char	**allocate_double(int count)
{
	return (ft_calloc((count + 1), sizeof(char *)));
}

static char	***allocate_groups(int count)
{
	return (ft_calloc((count + 1), sizeof(char **)));
}

void	redirections_and_tokens(t_exec *exec, char **tokens)
{
	while (tokens && tokens[exec->count])
	{
		if (tokens && tokens[exec->count][0] == '<'
			&& tokens[exec->count][1] == '\0')
			exec->redir_in++;
		if ((tokens && tokens[exec->count][0] == '>'
				&& tokens[exec->count][1] == '\0') || (tokens
			&& tokens[exec->count][0] == '>' && tokens[exec->count][1] == '>'
				&& tokens[exec->count][2] == '\0'))
			exec->redir_out++;
		exec->count++;
	}
	exec->infile_name = allocate_double(exec->redir_in);
	exec->outfile_name = allocate_double(exec->redir_out);
	exec->append = ft_calloc(sizeof(int), exec->redir_out);
}

void	split_pipeline_groups(t_exec *exec, char **tokens)
{
	init_exec(exec);
	redirections_and_tokens(exec, tokens);
	if (!exec->infile_name || !exec->outfile_name)
		return ;
	exec->groups = allocate_groups(exec->count);
	if (!exec->groups)
		free_exec(exec, 1, "Error malloc <split_pipeline_groups>", NULL);
	exec->cmds = allocate_double(exec->count);
	if (!exec->cmds)
		free_exec(exec, 1, "Error malloc <split_pipeline_groups>", NULL);
	split_groups(exec, tokens);
	if (exec->ncmd > 0)
	{
		finalize_group(exec);
		if (exec->group)
		{
			exec->groups[exec->ng] = exec->group;
			exec->ng = exec->ng + 1;
		}
	}
	exec->groups[exec->ng] = NULL;
	exec->infile_name[exec->ng] = NULL;
	exec->outfile_name[exec->ng] = NULL;
	free(exec->cmds);
}

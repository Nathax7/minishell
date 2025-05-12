/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_group.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:57:38 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/12 15:37:03 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static int	is_token(const char *tok, const char *s)
{
	return (ft_strcmp(tok, s) == 0);
}

static void	is_infile(t_exec *exec, char **tokens)
{
	exec->infile_name[exec->ng] = ft_strdup(tokens[exec->i + 1]);
	// open_infile_exec(exec, exec->infile_name[exec->ng]);
	// close(exec->infile);
	exec->i = exec->i + 2;
}

static void	is_outfile(t_exec *exec, char **tokens)
{
	exec->outfile_name[exec->ng] = ft_strdup(tokens[exec->i + 1]);
	// open_outfile_exec(exec, exec->outfile_name[exec->ng], 1);
	// close(exec->outfile);
	exec->i = exec->i + 2;
}

static void	is_notpipe(t_exec *exec, char **tokens)
{
	exec->cmds[exec->ncmd] = ft_strdup(tokens[exec->i]);
	exec->ncmd = exec->ncmd + 1;
	exec->i = exec->i + 1;
}

void	split_groups(t_exec *exec, char **tokens)
{
	while (exec->i < exec->count)
	{
		if (is_token(tokens[exec->i], "<") && exec->i + 1 < exec->count)
			is_infile(exec, tokens);
		else if (is_token(tokens[exec->i], ">") && exec->i + 1 < exec->count)
		{
			is_outfile(exec, tokens);
			if (!(exec->i < exec->count && is_token(tokens[exec->i], ">")))
			{
				finalize_group(exec);
				if (!exec->group)
					break ;
				exec->groups[exec->ng] = exec->group;
				exec->ng = exec->ng + 1;
				exec->ncmd = 0;
			}
		}
		else if (is_token(tokens[exec->i], "|"))
			exec->i = exec->i + 1;
		else
			is_notpipe(exec, tokens);
	}
}

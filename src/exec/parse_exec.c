/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:22:59 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/22 20:58:10 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"


void	init_pipex(t_pipex *pipex)
{
	if (!pipex)
		return;

	pipex->pids = NULL;
	pipex->cmds = NULL;
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->infile_name = NULL;
	pipex->outfile_name = NULL;
	pipex->fd[0] = -1;
	pipex->fd[1] = -1;
	pipex->status = 0;
	pipex->here_doc = 0;
	pipex->cmd_nbr = 0;
	pipex->i_wait = 0;
	pipex->i = 0;
	pipex->envp = 0;
}

t_cmd	*create_cmd(char *cmd_str)
{
	t_cmd *new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return NULL;
	new_cmd->cmd = ft_strdup(cmd_str);
	new_cmd->cmd_args = NULL;
	new_cmd->paths = NULL;
	new_cmd->path = NULL;
	new_cmd->next = NULL;
	return new_cmd;
}

void	add_cmd_back(t_cmd **cmds, t_cmd *new_cmd)
{
	t_cmd *tmp;

	if (!*cmds)
	{
		*cmds = new_cmd;
		return;
	}
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

t_pipex parse_exec(char **line)
{
	t_pipex pipex;
	t_cmd *current;
	int i;

	i = 0;
	init_pipex(&pipex);
	while (line && line[i])
	{
		if (line[i][0] == '<')
		{
			if (line[i][1] && line[i][1] == '<')
				pipex.here_doc = 1;
			i++;
			pipex.infile_name = line[i];
			init_file(&pipex, INFILE);
			i++;
		}
		else if (line[i][0] == '>')
		{
			if (line[i][1] && line[i][1] == '>')
			{
				i++;
				pipex.outfile_name = line[i];
				init_file(&pipex, APPEND);
				i++;
			}
			else
			{
				i++;
				pipex.outfile_name = line[i];
				init_file(&pipex, OUTFILE);
				i++;
			}
		}
		else
		{
			if (line[i][0] == '|')
				i++;
			add_cmd_back(&pipex.cmds, create_cmd(line[i]));
			pipex.cmd_nbr++;
			i++;
		}
	}
	current = pipex.cmds;
	while (current)
	{
		printf("Commande: %s\n", current->cmd);
		current = current->next;
	}
	return (pipex);
}

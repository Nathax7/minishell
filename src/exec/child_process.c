/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:58:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/21 21:15:10 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	setup_redirections(t_cmd *cmd)
{
	if (cmd->type == INFILE || cmd->type == HEREDOC)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			free_cmd(cmd, 1, NULL, "Error dup2");
		if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			free_cmd(cmd, 1, NULL, "Error dup2");
		ft_close(cmd, INFILE);
		ft_close(cmd, OUTFILE);
	}
	else if (cmd->type == OUTFILE || cmd->type == APPEND)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			free_cmd(cmd, 1, NULL, "Error dup2");
		ft_close(cmd, OUTFILE);
		ft_close(cmd, INFILE);
	}
	else
	{
		if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			free_cmd(cmd, 1, NULL, "Error dup2");
		ft_close(cmd, OUTFILE);
		ft_close(cmd, INFILE);
	}
	ft_close(cmd, FD1);
}

static void	execute_child(t_cmd *cmd, char **envp)
{
	ft_close(cmd, FD0);
	setup_redirections(cmd);
	execute(cmd, envp);
}

void	child_process(t_cmd *cmd, char **envp)
{
	if (pipe(cmd->fd) == -1)
		free_cmd(cmd, 1, NULL, "Error pipe");
	cmd->pid = fork();
	if (cmd->pid == -1)
		free_cmd(cmd, 1, NULL, "Error pids");
	if (cmd->pid == 0)
		execute_child(cmd, envp);
	ft_close(cmd, FD1);
	if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
		free_cmd(cmd, 1, NULL, "Error dup2");
	ft_close(cmd, FD0);
}

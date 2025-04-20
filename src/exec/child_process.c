/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 22:58:16 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/20 21:56:24 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	setup_redirections(t_cmd *cmd)
{
	if (cmd->i == 0)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			free_cmd(cmd, 1, NULL, "Error dup2");
		if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			free_cmd(cmd, 1, NULL, "Error dup2");
		ft_close(cmd, INFILE);
		ft_close(cmd, OUTFILE);
	}
	else if (cmd->i == cmd->cmd_nbr - 1)
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

static void	execute_child(t_cmd *cmd, char *argv, char **envp)
{
	ft_close(cmd, FD0);
	setup_redirections(cmd);
	execute_bonus(cmd, argv, envp);
}

void	child_process(t_cmd *cmd, char *argv, char **envp)
{
	if (pipe(cmd->fd) == -1)
		free_cmd(cmd, 1, NULL, "Error pipe");
	cmd->pids[cmd->i] = fork();
	if (cmd->pids[cmd->i] == -1)
		free_cmd(cmd, 1, NULL, "Error pids");
	if (cmd->pids[cmd->i] == 0)
		execute_child(cmd, argv, envp);
	ft_close(cmd, FD1);
	if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
		free_cmd(cmd, 1, NULL, "Error dup2");
	ft_close(cmd, FD0);
}

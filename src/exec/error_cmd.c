/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:10:01 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/14 17:38:44 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

// Fonction pour afficher str (msg personalisé) et/ou str2 (msg personalisé + msg d'erreur)
void msg_cmd(char *str, char *str2)
{
	ft_putstr_fd("cmd: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
		if (str2)
			ft_putstr_fd(": ", 2);
		else
			ft_putstr_fd("\n", 2);
	}
	if (str2)
		perror(str2);
}

// Fonction pour libérer la mémoire et fermer les fichiers ouverts et afficher un msg si voulu
void	free_parent_cmd(t_cmd *cmd, int status, char *str, char *str2)
{
	if (!cmd)
	{
		delete_list(cmd->alloc);
		if (status != -1)
			exit(status);
		return;
	}
	msg_cmd(str, str2);
	if (cmd->paths)
		ft_freesplit(cmd->paths);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	if (cmd->fd[0] >= 0)
		close(cmd->fd[0]);
	if (cmd->fd[1] >= 0)
		close(cmd->fd[1]);
	if (cmd->cmd_args)
		ft_freesplit(cmd->cmd_args);
	if (cmd->here_doc == HEREDOC && cmd->infile_name)
	{
		if (unlink(cmd->infile_name) == -1)
			msg_cmd(cmd->infile_name, NULL);
		free(cmd->infile_name);
	}
	delete_list(cmd->alloc);
	if (status != -1)
		exit(status);
}

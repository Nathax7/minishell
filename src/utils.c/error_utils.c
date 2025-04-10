/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:50:36 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/10 16:01:36 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

// Fonction pour afficher str (msg personalisé) et/ou str2 (msg personalisé + msg d'erreur)
void msg_utils(char *str, char *str2)
{
	ft_putstr_fd("utils: ", 2);
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
void	free_parent_cmd(t_cmd *utils, int status, char *str, char *str2)
{
	msg_utils(str, str2);
	if (utils->paths)
		ft_freesplit(utils->paths);
	if (utils->infile >= 0)
		close(utils->infile);
	if (utils->outfile >= 0)
		close(utils->outfile);
	if (utils->fd[0] >= 0)
		close(utils->fd[0]);
	if (utils->fd[1] >= 0)
		close(utils->fd[1]);
	if (utils->cmd_args)
		ft_freesplit(utils->cmd_args);
	if (utils->here_doc == HEREDOC)
		if (unlink(utils->infile_name) == -1)
			msg_utils(utils->infile_name, NULL);
	if (utils->infile_name && utils->here_doc == HEREDOC)
		free(utils->infile_name);
	delete_list(g_signal.node);
	if (status != -1)
		exit(status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:23:18 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/29 18:34:19 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	open_here_doc(t_files *files)
{
	int	fd;

	fd = open(files->infile_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_message("<open_infile>", strerror(errno), NULL);
		return (-1);
	}
	if (access(files->infile_name, F_OK) == -1)
	{
		ft_message("No such file or directory", files->infile_name, NULL);
		return (-1);
	}
	return (fd);
}

void	struct_open_infile(t_exec *exec)
{
	t_files	*current;
	int		previous_fd;

	exec->cmd_list->fd_input = -1;
	if (!exec->cmd_list->files)
		return ;
	current = exec->cmd_list->files;
	while (current)
	{
		if (current->infile_name)
		{
			if (access(current->infile_name, F_OK) == -1)
			{
				ft_message(NULL, current->infile_name, "No such file or directory");
				exec->cmd_list->fd_input = -2;
				exec->has_input_error = 1;
				return ;
			}
			if (access(current->infile_name, R_OK) == -1)
			{
				ft_message(NULL, current->infile_name, "Permission denied");
				exec->cmd_list->fd_input = -2;
					// ← CORRECTION: marquer l'erreur avec -2
				return ;
			}
			exec->cmd_list->fd_input = open(current->infile_name, O_RDONLY);
			if (exec->cmd_list->fd_input == -1)
			{
				ft_message(current->infile_name, strerror(errno), NULL);
				exec->cmd_list->fd_input = -2;
					// ← CORRECTION: marquer l'erreur avec -2
				return ;
			}
			previous_fd = exec->cmd_list->fd_input;
		}
		current = current->next;
	}
}

void	struct_open_outfile(t_exec *exec)
{
	t_files	*current;
	int		previous_fd;
	int		flags;

	// NE PAS ouvrir les fichiers de sortie si il y a une erreur d'input
	if (exec->has_input_error)
		return ;
	exec->cmd_list->fd_output = -1;
	previous_fd = -1;
	if (!exec->cmd_list->files)
		return ;
	current = exec->cmd_list->files;
	while (current)
	{
		if (current->outfile_name)
		{
			if (previous_fd != -1)
				close(previous_fd);
			// Vérifier les permissions AVANT d'ouvrir
			if (access(current->outfile_name, F_OK) == 0
				&& access(current->outfile_name, W_OK) == -1)
			{
				ft_message(NULL, current->outfile_name, "Permission denied");
				exec->cmd_list->fd_output = -2; // Marquer l'erreur
				return ;
			}
			flags = O_WRONLY | O_CREAT;
			if (current->append)
				flags |= O_APPEND;
			else
				flags |= O_TRUNC;
			exec->cmd_list->fd_output = open(current->outfile_name, flags,
					0644);
			if (exec->cmd_list->fd_output == -1)
			{
				ft_message(NULL, current->outfile_name, strerror(errno));
				exec->cmd_list->fd_output = -2; // Marquer l'erreur
				return ;
			}
			previous_fd = exec->cmd_list->fd_output;
		}
		current = current->next;
	}
}

void	struct_open_files_in_order(t_exec *exec)
{
	t_files	*current;
	int		previous_input_fd;
	int		previous_output_fd;
	int		has_error;
	int		flags;

	previous_input_fd = -1;
	previous_output_fd = -1;
	has_error = 0;
	exec->cmd_list->fd_input = -1;
	exec->cmd_list->fd_output = -1;
	if (!exec->cmd_list->files)
		return ;
	current = exec->cmd_list->files;
	while (current && !has_error)
	{
		// TRAITER LES INPUTS
		if (current->infile_name)
		{
			if (previous_input_fd != -1)
				close(previous_input_fd);
			if (access(current->infile_name, F_OK) == -1)
			{
				ft_message(current->infile_name, "No such file or directory", NULL);
				exec->cmd_list->fd_input = -2;
				has_error = 1;
			}
			else if (access(current->infile_name, R_OK) == -1)
			{
				ft_message(current->infile_name, "Permission denied", NULL);
				exec->cmd_list->fd_input = -2;
				has_error = 1;
			}
			else
			{
				exec->cmd_list->fd_input = open(current->infile_name, O_RDONLY);
				if (exec->cmd_list->fd_input == -1)
				{
					ft_message(current->infile_name, strerror(errno), NULL);
					exec->cmd_list->fd_input = -2;
					has_error = 1;
				}
				else
				{
					previous_input_fd = exec->cmd_list->fd_input;
				}
			}
		}
		if (current->outfile_name && !has_error)
		{
			if (previous_output_fd != -1)
				close(previous_output_fd);
			// Vérifier les permissions AVANT d'ouvrir
			if (access(current->outfile_name, F_OK) == 0
				&& access(current->outfile_name, W_OK) == -1)
			{
				ft_message(NULL, current->outfile_name, "Permission denied");
				exec->cmd_list->fd_output = -2;
				has_error = 1;
			}
			else
			{
				flags = O_WRONLY | O_CREAT;
				if (current->append)
					flags |= O_APPEND;
				else
					flags |= O_TRUNC;
				exec->cmd_list->fd_output = open(current->outfile_name, flags,
						0644);
				if (exec->cmd_list->fd_output == -1)
				{
					ft_message(NULL, current->outfile_name, strerror(errno));
					exec->cmd_list->fd_output = -2;
					has_error = 1;
				}
				else
				{
					previous_output_fd = exec->cmd_list->fd_output;
				}
			}
		}
		current = current->next;
	}
}

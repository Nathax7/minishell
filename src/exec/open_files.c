/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:23:18 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/04 18:13:49 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	previous_fd = -1;
	if (!exec->cmd_list->files)
		return ;
	current = exec->cmd_list->files;
	while (current)
	{
		if (current->infile_name)
		{
			if (previous_fd != -1)
				close(previous_fd);
			if (access(current->infile_name, F_OK) == -1)
			{
				ft_message(NULL, current->infile_name,
					"No such file or directory");
				exec->cmd_list->fd_input = -2;
				exec->has_input_error = 1;
				return ;
			}
			if (access(current->infile_name, R_OK) == -1)
			{
				ft_message(NULL, current->infile_name, "Permission denied");
				exec->cmd_list->fd_input = -2;
				exec->has_input_error = 1;
				return ;
			}
			exec->cmd_list->fd_input = open(current->infile_name, O_RDONLY);
			if (exec->cmd_list->fd_input == -1)
			{
				ft_message(current->infile_name, strerror(errno), NULL);
				exec->cmd_list->fd_input = -2;
				exec->has_input_error = 1;
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
			if (access(current->outfile_name, F_OK) == 0
				&& access(current->outfile_name, W_OK) == -1)
			{
				ft_message(NULL, current->outfile_name, "Permission denied");
				exec->cmd_list->fd_output = -2;
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
				exec->cmd_list->fd_output = -2;
				return ;
			}
			previous_fd = exec->cmd_list->fd_output;
		}
		current = current->next;
	}
}

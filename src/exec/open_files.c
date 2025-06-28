/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:23:18 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/28 20:08:06 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_here_doc(t_files *files)
{
	int	fd;

	fd = open(files->infile_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_message("<open_infile>", strerror(errno));
		return (-1);
	}
	if (access(files->infile_name, F_OK) == -1)
	{
		ft_message("No such file or directory", files->infile_name);
		return (-1);
	}
	return (fd);
}

void	open_infile(t_exec *exec, int previous_fd)
{
    if (previous_fd != -1)
        close(previous_fd);
    if (access(exec->cmd_list->files->infile_name, F_OK) == -1)
    {
        free_child(exec, 1, exec->cmd_list->files->infile_name,
            "No such file or directory");
    }
    if (access(exec->cmd_list->files->infile_name, R_OK) == -1)
    {
        free_child(exec, 1, exec->cmd_list->files->infile_name,
            "Permission denied");
    }
    exec->cmd_list->fd_input = open(exec->cmd_list->files->infile_name,
            O_RDONLY);
    if (exec->cmd_list->fd_input == -1)
    {
        free_child(exec, 1, "<open_infile>", strerror(errno));
    }
}

void	open_outfile(t_exec *exec, int previous_fd)
{
    if (previous_fd != -1)
        close(previous_fd);
    if (access(exec->cmd_list->files->outfile_name, F_OK) == 0)
    {
        if (access(exec->cmd_list->files->outfile_name, W_OK) == -1)
            free_child(exec, 1, "Permission denied",
                exec->cmd_list->files->outfile_name);
    }
    if (exec->cmd_list->files->append == 1)
        exec->cmd_list->fd_output = open(exec->cmd_list->files->outfile_name,
                O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        exec->cmd_list->fd_output = open(exec->cmd_list->files->outfile_name,
                O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (exec->cmd_list->fd_output == -1)
    {
        if (errno == EACCES)
            free_child(exec, 1, exec->cmd_list->files->outfile_name,
                "Permission denied");
        else if (errno == ENOENT)
            free_child(exec, 1, exec->cmd_list->files->outfile_name,
                "No such file or directory");
        else
            free_child(exec, 1, exec->cmd_list->files->outfile_name,
                strerror(errno));
    }
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
			exec->cmd_list->files = current;
			open_infile(exec, previous_fd);
			previous_fd = exec->cmd_list->fd_input;
		}
		current = current->next;
	}
}

void	struct_open_outfile(t_exec *exec)
{
	t_files	*current;
	int		previous_fd;

	exec->cmd_list->fd_output = -1;
	previous_fd = -1;
	if (!exec->cmd_list->files)
		return ;
	current = exec->cmd_list->files;
	while (current)
	{
		if (current->outfile_name)
		{
			exec->cmd_list->files = current;
			open_outfile(exec, previous_fd);
			previous_fd = exec->cmd_list->fd_output;
		}
		current = current->next;
	}
}

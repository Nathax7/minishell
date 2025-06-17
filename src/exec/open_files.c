/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:23:18 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/17 19:02:57 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

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
		fprintf(stderr, "%s", exec->cmd_list->files->infile_name);
		free_child(exec, 1, "No such file or directory caca",
			exec->cmd_list->files->infile_name);
	}
	if (access(exec->cmd_list->files->infile_name, R_OK) == -1)
	{
		free_child(exec, 1, "permission denied",
			exec->cmd_list->files->infile_name);
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
	if (access(exec->cmd_list->files->outfile_name, F_OK) == 0)
	{
		if (access(exec->cmd_list->files->outfile_name, W_OK) == -1)
			free_child(exec, 1, "permission denied <child>",
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
		if (previous_fd != -1)
			close(previous_fd);
		free_child(exec, 1, "<open_outfile child>", strerror(errno));
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

// int	open_infile_cmd(t_cmd *cmd, char *infile)
// {
// 	if (access(infile, F_OK) == -1)
// 	{
// 		ft_message("No such file or directory", infile);
// 		return (1);
// 	}
// 	if (access(infile, R_OK) == -1)
// 	{
// 		ft_message("permission denied", infile);
// 		return (1);
// 	}
// 	cmd->input_fd = open(infile, O_RDONLY);
// 	if (cmd->input_fd == -1)
// 		return (1);
// 	close(cmd->input_fd);
// 	return (0);
// }

// int	open_outfile_cmd(t_cmd *cmd, char *outfile, int mode)
// {
// 	if (access(outfile, F_OK) == 0)
// 	{
// 		if (access(outfile, W_OK) == -1)
// 			ft_message("permission denied", outfile);
// 		return (1);
// 	}
// 	if (mode == 0)
// 		cmd->output_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else if (mode == 1)
// 		cmd->output_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (cmd->output_fd == -1)
// 	{
// 		ft_message("<open_outfile>", strerror(errno));
// 		return (1);
// 	}
// 	close(cmd->output_fd);
// 	return (0);
// }

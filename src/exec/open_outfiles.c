/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:25:18 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/29 15:48:07 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_outfile(t_exec *exec, t_files **current, int *flags)
{
	if (access((*current)->outfile_name, F_OK) == 0
		&& access((*current)->outfile_name, W_OK) == -1)
	{
		ft_message(NULL, (*current)->outfile_name, "Permission denied");
		exec->cmd_list->fd_output = -2;
		return (1);
	}
	*flags = O_WRONLY | O_CREAT;
	if ((*current)->append)
		*flags |= O_APPEND;
	else
		*flags |= O_TRUNC;
	exec->cmd_list->fd_output = open((*current)->outfile_name, *flags, 0644);
	return (0);
}

int	check_output(t_exec *exec, t_files **current)
{
	if (exec->cmd_list->fd_output == -1)
	{
		ft_message(NULL, (*current)->outfile_name, strerror(errno));
		exec->cmd_list->fd_output = -2;
		return (1);
	}
	return (0);
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
				safe_close(&previous_fd);
			if (check_outfile(exec, &current, &flags))
				return ;
			if (check_output(exec, &current))
				return ;
			previous_fd = exec->cmd_list->fd_output;
		}
		current = current->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:29:01 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/09 16:42:41 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void ft_close(t_exec *exec, t_type type)
{
	int ret = 0;

	if (type == INFILE || type == HEREDOC)
	{
		ret = close(exec->pipex.infile);
		exec->pipex.infile = -1;
	}
	else if (type == OUTFILE || type == APPEND)
	{
		ret = close(exec->pipex.outfile);
		exec->pipex.outfile = -1;
	}
	else if (type == FD0)
	{
		ret = close(exec->pipex.fd[0]);
		exec->pipex.fd[0] = -1;
	}
	else if (type == FD1)
	{
		ret = close(exec->pipex.fd[1]);
		exec->pipex.fd[1] = -1;
	}
	if (ret == -1)
		free_pipex(exec, 1, NULL, "Error close");
}



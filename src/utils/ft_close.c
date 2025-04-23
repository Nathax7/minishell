/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:29:01 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/23 18:41:48 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void ft_close(t_pipex *pipex, t_type type)
{
	int ret = 0;

	if (type == INFILE || type == HEREDOC)
	{
		ret = close(pipex->infile);
		pipex->infile = -1;
	}
	else if (type == OUTFILE || type == APPEND)
	{
		ret = close(pipex->outfile);
		pipex->outfile = -1;
	}
	else if (type == FD0)
	{
		ret = close(pipex->fd[0]);
		pipex->fd[0] = -1;
	}
	else if (type == FD1)
	{
		ret = close(pipex->fd[1]);
		pipex->fd[1] = -1;
	}
	if (ret == -1)
		free_pipex(pipex, 1, NULL, "Error close");
}



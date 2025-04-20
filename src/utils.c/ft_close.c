/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:29:01 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 21:44:24 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void ft_close(t_cmd *cmd, t_close type)
{
	int ret = 0;

	if (type == INFILE)
		ret = close(cmd->infile), cmd->infile = -1;
	else if (type == OUTFILE)
		ret = close(cmd->outfile), cmd->outfile = -1;
	else if (type == FD0)
		ret = close(cmd->fd[0]), cmd->fd[0] = -1;
	else if (type == FD1)
		ret = close(cmd->fd[1]), cmd->fd[1] = -1;

	if (ret == -1)
		free_cmd(cmd, 1, NULL, "Error close");
}



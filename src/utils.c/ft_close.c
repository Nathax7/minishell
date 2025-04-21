/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:29:01 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/21 18:41:05 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void ft_close(t_cmd *cmd, t_type type)
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



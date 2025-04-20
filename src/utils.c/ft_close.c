/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 20:29:01 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 20:40:01 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

void ft_close(t_cmd *cmd, char *str)
{
	if (str == "infile")
	{
		if (close(cmd->infile) == -1)
			free_cmd(cmd, 1, NULL, "minishell: close");
		cmd->infile = -1;
	}
	if (str == "outfile")
	{
		if (close(cmd->outfile) == -1)
			free_cmd(cmd, 1, NULL, "minishell: close");
		cmd->outfile = -1;
	}
	if (str == "fd[0]")
	{
		if (close(cmd->fd[0]) == -1)
			free_cmd(cmd, 1, NULL, "minishell: close");
		cmd->fd[0] = -1;
	}
	if (str == "fd[1]")
	{
		if (close(cmd->fd[1]) == -1)
			free_cmd(cmd, 1, NULL, "minishell: close");
		cmd->fd[1] = -1;
	}
}

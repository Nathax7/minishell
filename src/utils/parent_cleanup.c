/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 20:03:17 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/24 15:31:09 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static void	restore_parent_fds(t_exec *exec)
{
	if (exec->stdin_backup != -1)
	{
		dup_and_close(&exec->stdin_backup, STDIN_FILENO);
		exec->stdin_backup = -1;
	}
	if (exec->stdout_backup != -1)
	{
		dup_and_close(&exec->stdout_backup, STDOUT_FILENO);
		exec->stdout_backup = -1;
	}
}

void	free_parent(t_exec *exec, int status, char *str1, char *str2)
{
	if (!exec)
		return ;
	if (str1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str1, 2);
		if (str2)
			ft_putstr_fd(": ", 2);
		else
			ft_putstr_fd("\n", 2);
	}
	if (str2)
	{
		ft_putstr_fd(str2, 2);
		ft_putstr_fd("\n", 2);
	}
	cleanup_cmd_list(exec, 1);
	cleanup_child_resources(exec);
	restore_parent_fds(exec);
	if (status != -1)
		exit(status);
}

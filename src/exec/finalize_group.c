/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_group.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:01:32 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/12 15:05:42 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

static void	finalize_group2(t_exec *exec)
{
	exec->group[exec->j] = exec->cmds[exec->j];
		exec->j = exec->j + 1;
}

void finalize_group(t_exec *exec)
{
	exec->group = malloc((exec->ncmd + 1) * sizeof(char *));
	if (!exec->group)
		return ;
	if (!exec->ncmd)
	{
		exec->group[0] = NULL;
		return ;
	}
	exec->j = 0;
	while (exec->j < exec->ncmd)
		finalize_group2(exec);
	exec->group[exec->j] = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:39:17 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/29 14:28:36 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_init(t_exec *exec, char **envp)
{
	size_t	i;

	ft_memset(exec, 0, sizeof(t_exec));
	exec->envp = envp;
	exec->envp_exists = 1;
	exec->stdin_backup = dup(STDIN_FILENO);
	exec->stdout_backup = dup(STDOUT_FILENO);
	i = 0;
	while (envp && envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp || !envp[i])
	{
		exec->envp_exists = 0;
		return ;
	}
	exec->paths = ft_split(envp[i] + 5, ':');
	if (!exec->paths)
		free_parent(exec, 1, "malloc", strerror(errno));
}

void	parsing_exec(t_token *tokens, t_exec *exec, char ***envp_ptr)
{
	if (!tokens || !exec)
		return ;
	exec->cmd_list = parsing_cmd(tokens, envp_ptr);
	free_token_list(tokens);
	tokens = NULL;
	if (!exec->cmd_list)
		return ;
}

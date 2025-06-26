/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:39:17 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/25 19:56:37 by nagaudey         ###   ########.fr       */
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
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp || !envp[i])
	{
		exec->envp_exists = 0;
		return ;
	}
	exec->paths = ft_split(envp[i] + 5, ':');
	if (!exec->paths)
		free_parent(exec, 1, "minishell: malloc: %s\n", strerror(errno));
}

void parsing_exec(t_token *tokens, t_exec *exec)
{
	if (!tokens || !exec)
		return ;
	exec->cmd_list = parsing_cmd(tokens);
	if (!exec->cmd_list)
		return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/19 18:51:57 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex: ./minishell <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./minishell \"here_doc\" <LIMITER> <cmd> <cmd1>"
					"<...> <file>\n",
					1);
	return (-1);
}

static void	free_pipes(t_exec *exec, int failed_index)
{
	int j;

	j = 0;
	while (j < failed_index)
	{
		if (exec->pipes[j])
		{
			if (exec->pipes[j][0] != -1)
				close(exec->pipes[j][0]);
			if (exec->pipes[j][1] != -1)
				close(exec->pipes[j][1]);
			free(exec->pipes[j]);
		}
		j++;
	}
	free(exec->pipes);
	exec->pipes = NULL;
}

void	create_pipes(t_exec *exec)
{
	int	i;

	if (!exec || exec->cmd_count <= 1)
		return ;
	exec->pipes = ft_calloc(exec->cmd_count - 1, sizeof(int *));
	if (!exec->pipes)
		free_parent(exec, 1, "Error create_pipes", NULL);
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		exec->pipes[i] = ft_calloc(2, sizeof(int));
		if (!exec->pipes[i])
		{
			free_pipes(exec, i);
			free_parent(exec, 1, "Error create_pipes", NULL);
		}
		if (pipe(exec->pipes[i]) == -1)
		{
			free(exec->pipes[i]);
			free_pipes(exec, i);
			free_parent(exec, 1, "Error create_pipes", NULL);
		}
		i++;
	}
}

int	pipex(t_token *tokens, char **envp)
{
	t_exec	exec;
	int		i;

	exec_init(&exec, envp);
	parsing_exec(tokens, &exec);
	// print_cmd_list_detailed(exec.cmd_list);
	if (!exec.cmd_list)
	{
		free_parent(&exec, 1, "Error: No commands parsed", NULL);
		return (1);
	}
	exec.cmd_count = find_size_cmd(exec.cmd_list);
	if (exec.cmd_count < 1)
		return (usage());
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		free_parent(&exec, 1, "malloc", strerror(errno));
	create_pipes(&exec);
	i = -1;
	if (exec.cmd_count > 1)
		while (++i < exec.cmd_count)
		{
			child_process(&exec, i, envp);
			exec.cmd_list = exec.cmd_list->next;
		}
	else
		exec_one(&exec, envp);
	i = -1;
	while (++i < exec.cmd_count)
		waitpid(exec.pids[i], &exec.exit_status, 0);
	free_parent_pipex(&exec, -1);
	if (WIFEXITED(exec.exit_status))
		return (WEXITSTATUS(exec.exit_status));
	return (exec.exit_status);
}

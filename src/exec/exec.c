/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 17:51:18 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_builtins(t_exec *exec, char ***envp_ptr)
{
	exec->exit_status = execute_single_builtin_in_parent(exec, envp_ptr);
	free_parent(exec, -1, NULL, NULL);
	return (exec->exit_status);
}

void	ft_childs(t_exec *exec, char ***envp_ptr)
{
	int	i;

	i = -1;
	while (++i < exec->cmd_count)
	{
		child_process(exec, i, *envp_ptr);
		exec->cmd_list = exec->cmd_list->next;
	}
}

void	print_flag(int flag)
{
	if (flag == 1)
	{
		ft_putstr_fd("\n", 2);
	}
	else if (flag == 2)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

void	ft_waitpid(t_exec *exec)
{
	int	i;
	int	status;
	int	flag;

	i = -1;
	flag = 0;
	while (++i < exec->cmd_count)
	{
		waitpid(exec->pids[i], &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			flag = 1;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			flag = 2;
		if (i == exec->cmd_count - 1)
		{
			if (WIFEXITED(status))
				exec->exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				exec->exit_status = 128 + WTERMSIG(status);
		}
	}
	print_flag(flag);
}

int	exec(t_token *tokens, char ***envp_ptr)
{
	t_exec	exec;
	t_cmd	*head;

	exec_init(&exec, *envp_ptr);
	parsing_exec(tokens, &exec, envp_ptr);
	if (!exec.cmd_list)
		return (1);
	exec.cmd_count = find_size_cmd(exec.cmd_list);
	head = exec.cmd_list;
	if (exec.cmd_count == 1 && exec.cmd_list->is_builtin)
		return (ft_builtins(&exec, envp_ptr));
	setup_parent_signals();
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		return (1);
	create_pipes(&exec);
	ft_childs(&exec, envp_ptr);
	close_all_pipes(&exec);
	ft_waitpid(&exec);
	exec.cmd_list = head;
	free_parent(&exec, -1, NULL, NULL);
	setup_interactive_signals();
	return (exec.exit_status);
}

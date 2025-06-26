/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/26 19:56:33 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	int	j;

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

void	close_remaining_pipes(t_exec *exec)
{
	int	i;

	if (!exec || !exec->pipes)
		return ;
	i = 0;
	while (i < exec->cmd_count - 1)
	{
		if (exec->pipes[i])
		{
			if (exec->pipes[i][0] != -1)
			{
				close(exec->pipes[i][0]);
				exec->pipes[i][0] = -1;
			}
			if (exec->pipes[i][1] != -1)
			{
				close(exec->pipes[i][1]);
				exec->pipes[i][1] = -1;
			}
		}
		i++;
	}
}

void	execute_single_builtin(t_exec *exec, char **envp)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = -1;
	stdout_backup = -1;
	if (exec->cmd_list->fd_input != -1 || exec->cmd_list->fd_output != -1)
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
	}
	struct_open_infile(exec);
	struct_open_outfile(exec);
	if (exec->cmd_list->fd_input != -1)
	{
		if (dup2(exec->cmd_list->fd_input, STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			close(exec->cmd_list->fd_input);
			if (stdin_backup != -1)
				close(stdin_backup);
			if (stdout_backup != -1)
				close(stdout_backup);
			return ;
		}
		close(exec->cmd_list->fd_input);
	}
	if (exec->cmd_list->fd_output != -1)
	{
		if (dup2(exec->cmd_list->fd_output, STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			close(exec->cmd_list->fd_output);
			if (stdin_backup != -1)
			{
				dup2(stdin_backup, STDIN_FILENO);
				close(stdin_backup);
			}
			if (stdout_backup != -1)
				close(stdout_backup);
			return ;
		}
		close(exec->cmd_list->fd_output);
	}
	is_builtin(exec, envp);
	if (stdin_backup != -1)
	{
		if (dup2(stdin_backup, STDIN_FILENO) == -1)
			perror("restore stdin");
		close(stdin_backup);
	}
	if (stdout_backup != -1)
	{
		if (dup2(stdout_backup, STDOUT_FILENO) == -1)
			perror("restore stdout");
		close(stdout_backup);
	}
}

int	pipex(t_token *tokens, char **envp)
{
	t_exec	exec;
	int		i;
	int		fork;
	t_cmd	*head;

	fork = 1;
	exec_init(&exec, envp);
	parsing_exec(tokens, &exec);
	if (!exec.cmd_list)
	{
		free_parent(&exec, 1, "Error: No commands parsed", NULL);
		return (1);
	}
	head = exec.cmd_list;
	exec.cmd_count = find_size_cmd(exec.cmd_list);
	if (exec.cmd_count < 1)
		return (usage());
	if (exec.cmd_count == 1 && exec.cmd_list->is_builtin)
		execute_single_builtin(&exec, envp);
	else
	{
		exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
		if (!exec.pids)
			free_parent(&exec, 1, "malloc", strerror(errno));
		create_pipes(&exec);
		i = -1;
		while (++i < exec.cmd_count)
		{
			child_process(&exec, i, envp);
			exec.cmd_list = exec.cmd_list->next;
		}
		close_remaining_pipes(&exec);
		i = -1;
		while (++i < exec.cmd_count && fork)
			waitpid(exec.pids[i], &exec.exit_status, 0);
	}
	exec.cmd_list = head;
	free_parent_pipex(&exec, -1);
	if (WIFEXITED(exec.exit_status))
		return (WEXITSTATUS(exec.exit_status));
	return (exec.exit_status);
}

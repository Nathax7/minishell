/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/17 22:39:56 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	free_token(t_token *token, int status, char *str, char *str2)
{
	t_token	*tmp;

	if (!token)
	{
		if (status != -1)
			exit(status);
		return ;
	}
	ft_message(str, str2);
	while (token)
	{
		tmp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = tmp;
	}
	if (status != -1)
		exit(status);
}
void	ft_message(char *str, char *str2)
{
	ft_putstr_fd("minishell: ", 2);
	if (str)
	{
		ft_putstr_fd(str, 2);
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
}

static void	free_args_list(t_args *args)
{
	t_args	*current;
	t_args	*next;

	current = args;
	while (current)
	{
		next = current->next;
		if (current->cmd_args)
		{
			free(current->cmd_args);
			current->cmd_args = NULL;
		}
		free(current);
		current = next;
	}
}

static void	free_files_list(t_files *files)
{
	t_files	*current;
	t_files	*next;

	current = files;
	while (current)
	{
		next = current->next;
		if (current->infile_name)
		{
			free(current->infile_name);
			current->infile_name = NULL;
		}
		if (current->outfile_name)
		{
			free(current->outfile_name);
			current->outfile_name = NULL;
		}
		free(current);
		current = next;
	}
}

int unlink_heredoc(t_files *files)
{
	t_files	*current;

	if (!files)
		return (0);
	current = files;
	while (current)
	{
		if (current->heredoc)
		{
			if (access(files->outfile_name, F_OK) == -1)
			{
				ft_message("error in unlink", NULL);
				return (1);
			}

			if (ft_strchr(files->infile_name, '/'))
			{
				ft_message("Error in unlink", NULL);
				return (1);
			}
			unlink(files->infile_name);
		}
		current = current->next;
	}
	return (0);
}

void	free_cmd_list(t_cmd *cmd_list, int is_parent)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			current->args = find_first_args(current->args);
			free_args_list(current->args);
			current->args = NULL;
		}
		if (!is_parent && current->cmd_path)
		{
			free(current->cmd_path);
			current->cmd_path = NULL;
		}
		if (current->files)
		{
			current->files = find_first_files(current->files);
			unlink_heredoc(current->files);
			free_files_list(current->files);
			current->files = NULL;
		}
		if (!is_parent)
		{
			if (current->fd_input != -1)
			{
				close(current->fd_input);
				current->fd_input = -1;
			}
			if (current->fd_output != -1)
			{
				close(current->fd_output);
				current->fd_output = -1;
			}
		}
		free(current);
		current = next;
	}
}

void	free_parent(t_exec *exec, int status, char *str, char *str2)
{
	ft_message(str, str2);
	if (!exec)
		return ;
	if (exec->cmd_list)
	{
		exec->cmd_list = find_first_cmd(exec->cmd_list);
		free_cmd_list(exec->cmd_list, 1);
		exec->cmd_list = NULL;
	}
	if (exec->paths)
	{
		free_split(exec->paths);
		exec->paths = NULL;
	}
	if (exec->pids)
	{
		free(exec->pids);
		exec->pids = NULL;
	}
	if (exec->pipes)
	{
		close_all_pipes(exec);
		exec->pipes = NULL;
	}
	if (exec->stdin_backup != -1)
	{
		dup2(exec->stdin_backup, STDIN_FILENO);
		close(exec->stdin_backup);
		exec->stdin_backup = -1;
	}
	if (exec->stdout_backup != -1)
	{
		dup2(exec->stdout_backup, STDOUT_FILENO);
		close(exec->stdout_backup);
		exec->stdout_backup = -1;
	}
	exec->envp = NULL;
	exec->cmd_count = 0;
	exec->exit_status = 0;
	exec->envp_exists = 0;
	if (status != -1)
		exit(status);
}

void	close_all_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	if (!exec->pipes)
		return ;
	while (i < exec->cmd_count - 1)
	{
		if (exec->pipes[i])
		{
			if (exec->pipes[i][0] >= 0)
				close(exec->pipes[i][0]);
			if (exec->pipes[i][1] >= 0)
				close(exec->pipes[i][1]);
		}
		i++;
	}
}

void	free_child(t_exec *exec, int status, char *str, char *str2)
{
	ft_message(str, str2);
	if (!exec)
		return ;
	if (exec->cmd_list)
	{
		exec->cmd_list = find_first_cmd(exec->cmd_list);
		free_cmd_list(exec->cmd_list, 0);
		exec->cmd_list = NULL;
	}
	if (exec->paths)
	{
		free_split(exec->paths);
		exec->paths = NULL;
	}
	if (exec->pids)
	{
		free(exec->pids);
		exec->pids = NULL;
	}
	if (exec->pipes)
	{
		close_all_pipes(exec);
		exec->pipes = NULL;
	}
	if (exec->stdin_backup != -1)
	{
		close(exec->stdin_backup);
		exec->stdin_backup = -1;
	}

	if (exec->stdout_backup != -1)
	{
		close(exec->stdout_backup);
		exec->stdout_backup = -1;
	}
	exec->envp = NULL;
	exec->cmd_count = 0;
	exec->exit_status = 0;
	exec->envp_exists = 0;
	if (status != -1)
		exit(status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_cleanup_backup.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/23 15:52:07 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

// void	free_token(t_token *token, int status, char *str, char *str2)
// {
// 	t_token	*tmp;

// 	if (!token)
// 	{
// 		if (status != -1)
// 			exit(status);
// 		return ;
// 	}
// 	ft_message(str, str2, NULL);
// 	while (token)
// 	{
// 		tmp = token->next;
// 		if (token->value)
// 			free(token->value);
// 		free(token);
// 		token = tmp;
// 	}
// 	if (status != -1)
// 		exit(status);
// }

// static void	free_args_list(t_args *args)
// {
// 	t_args	*current;
// 	t_args	*next;

// 	current = args;
// 	while (current)
// 	{
// 		next = current->next;
// 		if (current->cmd_args)
// 		{
// 			free(current->cmd_args);
// 			current->cmd_args = NULL;
// 		}
// 		free(current);
// 		current = next;
// 	}
// }

// static void	free_files_list(t_files *files)
// {
// 	t_files	*current;
// 	t_files	*next;

// 	current = files;
// 	while (current)
// 	{
// 		next = current->next;
// 		if (current->infile_name)
// 		{
// 			free(current->infile_name);
// 			current->infile_name = NULL;
// 		}
// 		if (current->outfile_name)
// 		{
// 			free(current->outfile_name);
// 			current->outfile_name = NULL;
// 		}
// 		free(current);
// 		current = next;
// 	}
// }

// int	unlink_heredoc(t_files *files)
// {
// 	t_files	*current;
// 	int		unlinked_count;

// 	if (!files)
// 		return (0);
// 	current = files;
// 	unlinked_count = 0;
// 	while (current)
// 	{
// 		if (current->heredoc && current->infile_name)
// 			unlink(current->infile_name);
// 		current = current->next;
// 	}
// 	return (unlinked_count);
// }

// void	free_cmd_list(t_cmd *cmd_list, int is_parent)
// {
// 	t_cmd	*current;
// 	t_cmd	*next;

// 	if (!cmd_list)
// 		return ;
// 	current = cmd_list;
// 	while (current)
// 	{
// 		next = current->next;
// 		if (current->args)
// 		{
// 			current->args = find_first_args(current->args);
// 			free_args_list(current->args);
// 			current->args = NULL;
// 		}
// 		if (!is_parent && current->cmd_path)
// 		{
// 			free(current->cmd_path);
// 			current->cmd_path = NULL;
// 		}
// 		if (current->files)
// 		{
// 			current->files = find_first_files(current->files);
// 			if (is_parent)
// 				unlink_heredoc(current->files);
// 			free_files_list(current->files);
// 			current->files = NULL;
// 		}
// 		if (!is_parent)
// 		{
// 			if (current->fd_input != -1)
// 			{
// 				safe_close(&current->fd_input);
// 				current->fd_input = -1;
// 			}
// 			if (current->fd_output != -1)
// 			{
// 				safe_close(&current->fd_output);
// 				current->fd_output = -1;
// 			}
// 		}
// 		free(current);
// 		current = next;
// 	}
// }

// void	close_all_pipes(t_exec *exec)
// {
// 	int	i;

// 	if (!exec || !exec->pipes)
// 		return ;
// 	i = 0;
// 	while (i < exec->cmd_count - 1)
// 	{
// 		if (exec->pipes[i])
// 		{
// 			if (exec->pipes[i][0] > 2)
// 			{
// 				safe_close(&exec->pipes[i][0]);
// 				exec->pipes[i][0] = -1;
// 			}
// 			if (exec->pipes[i][1] > 2)
// 			{
// 				safe_close(&exec->pipes[i][1]);
// 				exec->pipes[i][1] = -1;
// 			}
// 			free(exec->pipes[i]);
// 			exec->pipes[i] = NULL;
// 		}
// 		i++;
// 	}
// 	free(exec->pipes);
// 	exec->pipes = NULL;
// }

// void	cleanup_cmd_list(t_exec *exec, int parent)
// {
// 	if (exec->cmd_list)
// 	{
// 		exec->cmd_list = find_first_cmd(exec->cmd_list);
// 		free_cmd_list(exec->cmd_list, parent);
// 		exec->cmd_list = NULL;
// 	}
// }
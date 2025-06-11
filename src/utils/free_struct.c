/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/11 16:14:45 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

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

void	free_exec_core(t_exec *node)
{
	t_exec	*head;
	t_exec	*next;
	char	**g;

	head = node;
	if (!head)
		return ;
	while (head->prev)
		head = head->prev;
	while (head)
	{
		next = head->next;
		if (head->group)
		{
			g = head->group;
			while (*g)
				free(*g++);
			free(head->group);
		}
		if (head->infile > STDERR_FILENO)
			close(head->infile);
		if (head->outfile > STDERR_FILENO)
			close(head->outfile);
		if (head->infile_name >= 0)
			free(head->infile_name);
		if (head->outfile_name >= 0)
			free(head->outfile_name);
		free(head);
		head = next;
	}
}

void	free_pipex_core(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->pipex.paths)
		ft_freesplit(exec->pipex.paths);
	if (exec->pipex.pids)
		free(exec->pipex.pids);
	// if (exec->pipex.here_doc == 1)
	// {
	// 	unlink(exec->infile_name);
	// 	free(exec->infile_name);
	// }
	if (exec->pipex.infile >= 0)
		close(exec->pipex.infile);
	if (exec->pipex.outfile >= 0)
		close(exec->pipex.outfile);
	if (exec->pipex.fd[0] >= 0)
		close(exec->pipex.fd[0]);
	if (exec->pipex.fd[1] >= 0)
		close(exec->pipex.fd[1]);
	if (exec->pipex.cmd_args)
		ft_freesplit(exec->pipex.cmd_args);
	exec->pipex.fd[0] = -1;
	exec->pipex.fd[1] = -1;
}

void	free_pipex(t_exec *exec, int status, char *str, char *str2)
{
	if (!exec)
	{
		if (status != -1)
			exit(status);
		return ;
	}
	if (str || str2)
		ft_message(str, str2);
	free_pipex_core(exec);
	free_exec_core(exec);
	if (status != -1)
		exit(status);
}

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

void	free_exec(t_exec *exec, int status, char *str, char *str2)
{
	if (!exec)
	{
		if (status != -1)
			exit(status);
		return ;
	}
	if (str || str2)
		ft_message(str, str2);
	free_exec_core(exec);
	if (status != -1)
		exit(status);
}
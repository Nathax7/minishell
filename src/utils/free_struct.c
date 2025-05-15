/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/14 17:43:38 by nagaudey         ###   ########.fr       */
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
		ft_putstr_fd(str2, 2);
}

void	free_exec_core(t_exec *exec)
{
	int i;
	int j;

	i = 0;
	if (exec->groups)
	{
		while (exec->groups[i])
		{
			j = 0;
			while (exec->groups[i][j])
			{
				if (exec->groups[i][j])
					free(exec->groups[i][j]);
				j++;
			}
			if (exec->groups[i])
				free(exec->groups[i]);
			i++;
		}
		if (exec->groups)
			free(exec->groups);
	}
	i = 0;
	// while (i <= exec->ng)
	// {
	// 	if (exec->infile_name)
	// 		free(exec->infile_name);
	// 	i++;
	// }
	// free(exec->infile_name);
	// while (i <= exec->ng)
	// {
	// 	if (exec->infile_name)
	// 		free(exec->outfile_name);
	// 	i++;
	// }
	free_split(exec->infile_name);
	free_split(exec->outfile_name);
	if (exec->append)
		free(exec->append);
}

// Deux fonctions pour liberer pipex fermer les fichiers ouverts et afficher un msg si voulu
static void	free_pipex_core(t_exec *exec)
{
	if (!exec)
		return ;
	free_exec_core(exec);
	if (exec->pipex.paths)
		ft_freesplit(exec->pipex.paths);
	if (exec->pipex.pids)
		free(exec->pipex.pids);
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
	if (exec->pipex.here_doc == 1 && exec->pipex.infile_name)
	{
		unlink(exec->pipex.infile_name);
		free(exec->pipex.infile_name);
	}
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


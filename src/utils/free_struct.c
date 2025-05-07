/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 17:37:32 by nagaudey         ###   ########.fr       */
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

// Deux fonctions pour liberer pipex fermer les fichiers ouverts et afficher un msg si voulu
static void	free_pipex_core(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->paths)
		ft_freesplit(pipex->paths);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (pipex->fd[0] >= 0)
		close(pipex->fd[0]);
	if (pipex->fd[1] >= 0)
		close(pipex->fd[1]);
	if (pipex->cmd_args)
		ft_freesplit(pipex->cmd_args);
	pipex->fd[0] = -1;
	pipex->fd[1] = -1;
	if (pipex->here_doc == 1 && pipex->infile_name)
	{
		unlink(pipex->infile_name);
		free(pipex->infile_name);
	}
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
                free(exec->groups[i][j]);
                j++;
            }
            free(exec->groups[i]);
            i++;
        }
        free(exec->groups);
    }
    if (exec->cmds)
        free(exec->cmds);
    if (exec->infile)
        free(exec->infile_name);
    if (exec->outfile)
        free(exec->outfile_name);
}

void	free_pipex(t_pipex *pipex, int status, char *str, char *str2)
{
	if (!pipex)
	{
		if (status != -1)
			exit(status);
		return ;
	}
	if (str || str2)
		ft_message(str, str2);
	free_pipex_core(pipex);
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


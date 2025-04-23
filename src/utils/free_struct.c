/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/23 18:41:27 by nagaudey         ###   ########.fr       */
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
		perror(str2);
}

// Deux fonctions pour liberer pipex fermer les fichiers ouverts et afficher un msg si voulu
static void	free_pipex_core(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->paths)
		ft_freesplit(pipex->paths);
	if (pipex->cmd_args)
		ft_freesplit(pipex->cmd_args);
	if (pipex->cmd)
		free(pipex->cmd);
// >= 0 c'est bon ou je mets plutot > 2 pour etre sur ? //
	if (pipex->infile  >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
	if (pipex->fd[0]  >= 0)
		close(pipex->fd[0]);
	if (pipex->fd[1]  >= 0)
		close(pipex->fd[1]);
	if (pipex->here_doc == 1 && pipex->infile_name)
	{
		unlink(pipex->infile_name);
		free(pipex->infile_name);
	}
}
// // // au cas ou
// // if (pipex->infile  > 2)
// 	close(pipex->infile);
// // if (pipex->outfile > 2)
// 	close(pipex->outfile);
// // if (pipex->fd[0]   > 2)
// 	close(pipex->fd[0]);
// // if (pipex->fd[1]   > 2)
// 	close(pipex->fd[1]);


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
	free(pipex);
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

// void	free_all(t_minishell *shell, int status, char *str, char *str2)
// {
// 	if (!shell)
// 	{
// 		if (status != -1)
// 			exit(status);
// 		return ;
// 	}
// 	free_pipex(&shell->pipex, status, str, str2);
// 	free_token(&shell->token, status, str, str2);
// 	if (status != -1)
// 		exit(status);
// }

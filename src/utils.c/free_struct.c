/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:11:14 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/20 16:03:51 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

/* fermer chaque node de la liste chainee t_cmd, sans gerer le message d'erreur (pour l'init et si besoin) */
void	free_cmd_list(t_cmd *lst)
{
	t_cmd	*next;

	while (lst)
	{
		next = lst->next;
		free_cmd(lst, -1, NULL, NULL);   /* -1  ⇒  no exit, no message */
		lst = next;
	}
}
/* fermer la liste chainee t_token, sans gerer le message d'erreur (pour l'init et si besoin) */
void	free_token_silent(t_token *lst)
{
	free_token(lst, -1, NULL, NULL);
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
		perror(str2);
}

// Fonction pour libérer la mémoire et fermer les fichiers ouverts et afficher un msg si voulu
void	free_cmd(t_cmd *cmd, int status, char *str, char *str2)
{
	if (!cmd)
	{
		if (status != -1)
			exit(status);
		return ;
	}
	ft_message(str, str2);
	if (cmd->paths)
		ft_freesplit(cmd->paths);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	if (cmd->fd[0] >= 0)
		close(cmd->fd[0]);

		ft_freesplit(cmd->cmd_args);
	if (cmd->here_doc == HEREDOC && cmd->infile_name)
	{
		if (unlink(cmd->infile_name) == -1)
			ft_message(cmd->infile_name, NULL);
		free(cmd->infile_name);
	}
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
// 	free_cmd(&shell->cmd, status, str, str2);
// 	free_token(&shell->token, status, str, str2);
// 	if (status != -1)
// 		exit(status);
// }

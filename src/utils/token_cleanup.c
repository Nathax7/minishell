/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 00:00:00 by nagaudey         #+#    #+#             */
/*   Updated: 2025/07/13 00:00:00 by nagaudey         ###   ########.fr       */
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
	ft_message(str, str2, NULL);
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

void	free_args_list(t_args *args)
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

void	free_files_list(t_files *files)
{
	t_files	*current;
	t_files	*next;

	if (!files)
		return ;
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

int	unlink_heredoc(t_files *files)
{
	t_files	*current;
	int		unlinked_count;

	if (!files)
		return (0);
	current = files;
	unlinked_count = 0;
	while (current)
	{
		if (current->heredoc && current->infile_name)
			unlink(current->infile_name);
		current = current->next;
	}
	return (unlinked_count);
}

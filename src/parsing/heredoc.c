/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:26:56 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/19 23:07:07 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	handle_heredocs(t_token *tokens, t_cmd *cmd)
{
	int		fd;
	char	*delim;
	char	*line;
	char	*temp;

	random_filename(cmd, token);
	while (tokens)
	{
		if (tokens->type == T_HEREDOC && tokens->next
			&& tokens->next->type == T_WORD)
		{
			delim = tokens->next->value;
			cmd->infile = open(cmd->infile_name, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
			temp = readline("> ");
			if (!temp)
				msg_cmd(NULL, "Error gnl");
			while (temp != NULL)
			{
				if (ft_strncmp(temp, delim, ft_strlen(delim)) == 0
					&& ft_strlen(temp) == ft_strlen(delim))
				{
					free(temp);
					break ;
				}
				write(cmd->infile, temp, ft_strlen(temp));
				write(cmd->infile, "\n", 1);
				free(temp);
				temp = readline("> ");
				if (!temp)
					msg_cmd(NULL, "Error readline");
			}
		}
		close(cmd->infile);
		tokens = tokens->next;
	}
}

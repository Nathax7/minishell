/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:07:18 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 21:52:15 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	open_tmp(char **path_out)
{
	static int	idx;
	char		*name;

	name = ft_strjoin("/tmp/msh_hd_", ft_itoa(idx++));
	if (!name)
		return (-1);
	*path_out = name;
	return (open(name, O_WRONLY | O_CREAT | O_TRUNC, 0600));
}

int	fill_heredocs(t_cmd *cmds)
{
	char	*line;
	int		fd;

	while (cmds)
	{
		if (cmds->here_doc == HEREDOC)
		{
			fd = open_tmp(&cmds->infile_name);        /* /tmp/msh_hd_N  */
			if (fd < 0)
				return (perror("heredoc"), 1);
			while (1)
			{
				line = readline("> ");
				if (!line || ft_strncmp(line, cmds->infile_name, \
						ft_strlen(cmds->infile_name) + 1) == 0)
					break ;
				ft_putendl_fd(line, fd);
				free(line);
			}
			free(line);
			close(fd);
			cmds->infile = open(cmds->infile_name, O_RDONLY);
		}
		cmds = cmds->next;
	}
	return (0);
}

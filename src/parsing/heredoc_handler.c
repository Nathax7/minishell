/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:20:16 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/26 17:55:37 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	*create_temp_file(void)
{
	char	*template;
	int		fd;

	template = ft_strdup("/tmp/minishell_XXXXXX");
	if (!template)
		return (NULL);
	fd = mkstemp(template);
	if (fd == -1)
		return (free(template), NULL);
	close(fd);
	return (template);
}

static void	write_heredoc_line(int fd, char *line, int should_expand,
		char **envp, int exit_status)
{
	char	*expanded;

	if (should_expand)
	{
		expanded = expand_variables_in_str(line, Q_DOUBLE, envp, exit_status);
		ft_putendl_fd(expanded ? expanded : line, fd);
		free(expanded);
	}
	else
		ft_putendl_fd(line, fd);
}

static int	is_delimiter_quoted(t_token *delimiter)
{
	return (delimiter->quote != Q_NONE);
}

char	*process_heredoc(t_token *delimiter, char **envp, int exit_status)
{
	char	*temp_file;
	char	*line;
	int		fd;
	int		should_expand;

	temp_file = create_temp_file();
	if (!temp_file)
		return (NULL);
	fd = open(temp_file, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (free(temp_file), NULL);
	should_expand = !is_delimiter_quoted(delimiter);
	while ((line = secure_readline("heredoc> ")))
	{
		if (ft_strcmp(line, delimiter->value) == 0)
		{
			free(line);
			close(fd);
			return (temp_file);
		}
		write_heredoc_line(fd, line, should_expand, envp, exit_status);
		free(line);
	}
	close(fd);
	unlink(temp_file);
	free(temp_file);
	return (NULL);
}

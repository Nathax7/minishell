/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:20:16 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/11 16:55:46 by almeekel         ###   ########.fr       */
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
		if (expanded)
		{
			ft_putendl_fd(expanded, fd);
			free(expanded);
		}
		else
		{
			ft_putendl_fd(line, fd);
		}
	}
	else
	{
		ft_putendl_fd(line, fd);
	}
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
	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (cleanup_and_return_char(NULL, -1, temp_file, 0));
	should_expand = !is_delimiter_quoted(delimiter);
	while ((line = readline("heredoc> ")))
	{
		if (g_signal_test == 130)
			return (cleanup_and_return_char(line, fd, temp_file, 0));
		if (ft_strcmp(line, delimiter->value) == 0)
			return (cleanup_and_return_char(line, fd, temp_file, 1));
		write_heredoc_line(fd, line, should_expand, envp, exit_status);
		free(line);
	}
	return (cleanup_and_return_char(line, fd, temp_file, 1));
}

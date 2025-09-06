/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:43:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 17:52:10 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_read_error(t_files *files, int *urandom_fd)
{
	safe_close(urandom_fd);
	free(files->infile_name);
	files->infile_name = NULL;
	return (1);
}

int	random_filename(t_files *files)
{
	int				urandom_fd;
	unsigned char	random;
	int				i;

	if (!files)
		return (1);
	files->infile_name = malloc(sizeof(char) * 22);
	if (!files->infile_name)
		return (1);
	ft_strcpy(files->infile_name, "/tmp/.heredoc_");
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		return (free_infile_name(files));
	i = 14;
	while (i < 21)
	{
		if (read(urandom_fd, &random, 1) < 0)
		{
			return (ft_read_error(files, &urandom_fd));
		}
		files->infile_name[i++] = CHARSET[random % (sizeof(CHARSET) - 1)];
	}
	files->infile_name[21] = '\0';
	safe_close(&urandom_fd);
	return (0);
}

void	is_delimiter(char **temp, char *limiter)
{
	if (!*temp)
	{
		ft_putstr_fd("minishell: warning: here-document"
			"at line 2 delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(limiter, 2);
		ft_putstr_fd("')\n", 2);
	}
	free(*temp);
}

char	*here_doc_input(t_files *files, char *limiter, int *fd)
{
	char	*temp;

	while (g_signal_status == 1)
	{
		temp = readline("> ");
		if (!temp || (ft_strncmp(temp, limiter, ft_strlen(limiter)) == 0
				&& ft_strlen(temp) == ft_strlen(limiter)))
		{
			is_delimiter(&temp, limiter);
			break ;
		}
		write(*fd, temp, ft_strlen(temp));
		write(*fd, "\n", 1);
		free(temp);
	}
	safe_close(fd);
	return (files->infile_name);
}

char	*here_doc(t_files *files, char *limiter)
{
	char	*infile_name;
	int		fd;

	g_signal_status = 1;
	if (random_filename(files) == 1)
		return (NULL);
	fd = open_here_doc(files);
	if (fd == -1)
		return (NULL);
	setup_heredoc_signals();
	infile_name = here_doc_input(files, limiter, &fd);
	setup_postheredoc_signals();
	if (!infile_name)
	{
		g_signal_status = 0;
		rl_done = 0;
		return (NULL);
	}
	return (infile_name);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:43:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 15:31:19 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	random_filename(t_pipex *pipex)
{
	int				urandom_fd;
	unsigned char	random;
	int				i;

	i = -1;
	pipex->infile_name = malloc(sizeof(char) * 9);
	if (!pipex->infile_name)
		free_pipex(pipex, 1, "malloc", strerror(errno));
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		free_pipex(pipex, 1, "open", strerror(errno));
	while (++i < 8)
	{
		if (read(urandom_fd, &random, 1) < 0)
		{
			close(urandom_fd);
			free_pipex(pipex, 1, "read", strerror(errno));
		}
		pipex->infile_name[i] = CHARSET[random % (sizeof(CHARSET) - 1)];
	}
	pipex->infile_name[8] = '\0';
	close(urandom_fd);
}

void	here_doc(t_pipex *pipex, char *limiter)
{
	char	*temp;

	pipex->infile = open(pipex->infile_name, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	temp = readline("> ");
	if (!temp)
		free_pipex(pipex, 1, "malloc", strerror(errno));
	while (temp != NULL)
	{
		if (ft_strncmp(temp, limiter, ft_strlen(limiter)) == 0 && ft_strlen(temp) == ft_strlen(limiter))
		{
			free(temp);
			break ;
		}
		write(pipex->infile, temp, ft_strlen(temp));
		write(pipex->infile, "\n", 1);
		free(temp);
		temp = readline("> ");
		if (!temp)
			free_pipex(pipex, 1, "malloc:", strerror(errno));
	}
	close(pipex->infile);
	pipex->infile = open(pipex->infile_name, O_RDONLY);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:43:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/25 21:22:30 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	{
		free(files->infile_name);
		files->infile_name = NULL;
		return (1);
	}
	i = 14;
	while (i < 22)
	{
		if (read(urandom_fd, &random, 1) < 0)
		{
			close(urandom_fd);
			free(files->infile_name);
			files->infile_name = NULL;
			return (1);
		}
		files->infile_name[i] = CHARSET[random % (sizeof(CHARSET) - 1)];
		i++;
	}
	files->infile_name[22 - 1] = '\0';
	close(urandom_fd);
	return (0);
}

char	*here_doc(t_files *files, char *limiter)
{
	char	*temp;
	int		fd;

	if (random_filename(files) == 1)
		return (NULL);
	fd = open_here_doc(files);
	if (fd == -1)
		return (NULL);
	temp = readline("> ");
	if (!temp)
		return (NULL);
	while (temp != NULL)
	{
		if (ft_strncmp(temp, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(temp) == ft_strlen(limiter))
		{
			free(temp);
			break ;
		}
		write(fd, temp, ft_strlen(temp));
		write(fd, "\n", 1);
		free(temp);
		temp = readline("> ");
		if (!temp)
			return (NULL);
	}
	close(fd);
	return (files->infile_name);
}


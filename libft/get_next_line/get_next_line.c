/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:10:25 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/19 17:29:22 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

static int	size_line(char *s1)
{
	size_t	len;

	if (!s1)
		len = 0;
	else
		len = ft_strlen(s1);
	return (len);
}

static char	*ft_strnjoin(char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*array;

	len = size_line(s1);
	array = (char *)malloc(len + n + 1);
	if (!array)
		return (free(s1), NULL);
	j = 0;
	i = 0;
	while (i < len)
	{
		array[i] = s1[i];
		i++;
	}
	while (s2[j] && j < n)
	{
		array[i + j] = s2[j];
		j++;
	}
	array[i + j] = '\0';
	free(s1);
	return (array);
}

static size_t	ft_strchrn(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (i - 1);
}

static ssize_t	read_buffer(int fd, char *buffer, char *line)
{
	ssize_t	count_read;

	if (buffer[0] == '\0')
	{
		count_read = read(fd, buffer, BUFFER_SIZE);
		if (count_read == 0)
			return (0);
		if (count_read < 0)
		{
			free(line);
			return (-1);
		}
		buffer[count_read] = '\0';
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	size_t		i;
	ssize_t		read_status;

	line = NULL;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		read_status = read_buffer(fd, buffer, line);
		if (read_status == 0)
			return (line);
		if (read_status < 0)
			return (NULL);
		i = ft_strchrn(buffer);
		line = ft_strnjoin(line, buffer, i + 1);
		if (buffer[i] == '\n')
		{
			ft_memmove(buffer, buffer + i + 1, BUFFER_SIZE - i);
			break ;
		}
		buffer[0] = '\0';
	}
	return (line);
}

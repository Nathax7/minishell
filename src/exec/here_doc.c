/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:43:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/21 16:56:31 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/exec.h"

// void	random_filename(t_exec *exec)
// {
// 	int				urandom_fd;
// 	unsigned char	random;
// 	int				i;

// 	i = -1;
// 	exec->pipex.infile_name = malloc(sizeof(char) * 9);
// 	if (!exec->pipex.infile_name)
// 		free_pipex(exec, 1, "malloc", strerror(errno));
// 	urandom_fd = open("/dev/urandom", O_RDONLY);
// 	if (urandom_fd < 0)
// 		free_pipex(exec, 1, "open", strerror(errno));
// 	while (++i < 8)
// 	{
// 		if (read(urandom_fd, &random, 1) < 0)
// 		{
// 			close(urandom_fd);
// 			free_pipex(exec, 1, "read", strerror(errno));
// 		}
// 		exec->pipex.infile_name[i] = CHARSET[random % (sizeof(CHARSET) - 1)];
// 	}
// 	exec->pipex.infile_name[8] = '\0';
// 	close(urandom_fd);
// }

// void	here_doc(t_exec *exec, char *limiter)
// {
// 	char	*temp;

// 	exec->pipex.infile = open(exec->pipex.infile_name,
// 			O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	temp = readline("> ");
// 	if (!temp)
// 		free_pipex(exec, 1, "malloc", strerror(errno));
// 	while (temp != NULL)
// 	{
// 		if (ft_strncmp(temp, limiter, ft_strlen(limiter)) == 0
// 			&& ft_strlen(temp) == ft_strlen(limiter))
// 		{
// 			free(temp);
// 			break ;
// 		}
// 		write(exec->pipex.infile, temp, ft_strlen(temp));
// 		write(exec->pipex.infile, "\n", 1);
// 		free(temp);
// 		temp = readline("> ");
// 		if (!temp)
// 			free_pipex(exec, 1, "malloc:", strerror(errno));
// 	}
// 	close(exec->pipex.infile);
// 	exec->pipex.infile = open(exec->pipex.infile_name, O_RDONLY);
// }

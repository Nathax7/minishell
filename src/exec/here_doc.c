/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:43:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/20 22:03:53 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	random_filename(t_cmd *cmd, t_token *token)
{
	int				urandom_fd;
	unsigned char	random;
	int				i;

	i = -1;
	cmd->infile_name = malloc(sizeof(char) * 9);
	if (!cmd->infile)
		free_cmd(cmd, 1, NULL, "Error malloc");
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		free_cmd(cmd, 1, NULL, "Error malloc");
	while (++i < 8)
	{
		if (read(urandom_fd, &random, 1) < 0)
		{
			close(urandom_fd);
			free_cmd(cmd, 1, NULL, "Error read");
		}
		cmd->infile_name[i] = CHARSET[random % (sizeof(CHARSET) - 1)];
	}
	cmd->infile_name[8] = '\0';
	close(urandom_fd);
}

void	here_doc(t_cmd *cmd, char *limiter)
{
	char	*temp;

	cmd->infile = open(cmd->infile_name, O_WRONLY | O_CREAT | O_TRUNC,
		0644);
	temp = readline("> ");
	if (!temp)
		msg_cmd(NULL, "Error gnl");
	while (temp != NULL)
	{
		if (ft_strncmp(temp, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(temp) == ft_strlen(limiter))
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
	ft_close(cmd, INFILE);
	cmd->infile = open(cmd->infile_name, O_RDONLY);
}

void init_cmd(t_cmd *cmd, char **envp)
{
	int i;

	i = 0;
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
			i++;
	if (!envp || !envp[i])
	{
		cmd->env = NO_ENV;
		return ;
	}
	cmd->paths = ft_split(envp[i] + 5, ':');
	if (!cmd->paths)
	free_cmd(cmd, 1, NULL, "Error malloc");
	open_infile(cmd, cmd->infile_name);
	if (cmd->append == APPEND)
		open_outfile(cmd, cmd->outfile_name, 0);
	else
		open_outfile(cmd, cmd->outfile_name, 1);
}
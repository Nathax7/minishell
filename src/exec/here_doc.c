/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:43:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/14 17:41:54 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

void	random_filename(t_cmd *cmd)
{
	int				urandom_fd;
	unsigned char	random;
	int				i;

	i = -1;
	cmd->infile_name = ft_malloc(sizeof(char) * 9, cmd->alloc);
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		free_parent_cmd(cmd, 1, NULL, "Error malloc");
	while (++i < 8)
	{
		if (read(urandom_fd, &random, 1) < 0)
		{
			close(urandom_fd);
			free_parent_cmd(cmd, 1, NULL, "Error read");
		}
		cmd->infile_name[i] = CHARSET[random % (sizeof(CHARSET) - 1)];
	}
	cmd->infile_name[8] = '\0';
	close(urandom_fd);
}

// int	ft_strcmp_for_heredoc(char *s1, char *s2)
// {
// 	char	*str;
// 	int		k;
// 	int		i;

// 	i = 0;
// 	if (!s1 || !s2)
// 		return (0);
// 	str = get_string(ft_strdup(s2), 0, 0, get_size(s2));
// 	while (s1[i] == str[i] && s1[i] != '\0' && str[i] != '\0')
// 		i++;
// 	k = s1[i] - str[i];
// 	free(str);
// 	return (k);
// }

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
			msg_cmd(NULL, "Error gnl");
	}
	close(cmd->infile);
	cmd->infile = open(cmd->infile_name, O_RDONLY);
}

void	is_here_doc(t_cmd *cmd, char **av, int ac)
{
	if (cmd->here_doc)
	{
		if (ac < 6)
		{
			cmd->here_doc = 0;
			free_parent_cmd(cmd, -1, NULL, NULL);
			usage();
		}
		random_filename(cmd);
		here_doc(cmd, av[2]);
		open_outfile(cmd, av[ac - 1], 0);
	}
	else
	{
		open_outfile(cmd, av[ac - 1], 1);
		open_infile(cmd, av[1]);
	}
}

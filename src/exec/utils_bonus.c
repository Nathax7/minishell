/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:03:03 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 15:24:03 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	pipex_init(t_pipex *pipex, char **envp)
{
	size_t	i;

	*pipex = (t_pipex){0};
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->here_doc = 1;
	pipex->i = -1;
	pipex->i_wait = -1;
	pipex->envp = 1;
	i = 0;
	while (envp && envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp || !envp[i])
	{
		pipex->envp = 0;
		return ;
	}
	pipex->paths = ft_split(envp[i] + 5, ':');
	if (!pipex->paths)
		if (errno == ENOMEM)
			free_pipex(pipex, -1, "malloc", strerror(errno));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 15:08:18 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1>"
					"<...> <file>\n",
					1);
	return (-1);
}

void	ft_parse(t_pipex *pipex, char **av, int ac)
{
	// if (ft_strncmp(av[0], "here_doc", 8) == 0)
	// {
	// 	if (ac < 5)
	// 	{
	// 		pipex->here_doc = 0;
	// 		free_parent(pipex, -1, NULL, NULL);
	// 		usage();
	// 	}
	if (pipex->append == 1)
	{
		open_infile(pipex, av[0]);
		open_outfile(pipex, av[ac - 1], 0);
	}
	else
	{
		pipex->here_doc = 0;
		open_infile(pipex, av[0]);
		open_outfile(pipex, av[ac - 1], 1);
	}
}

int	pipex(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 3)
		return (usage());
	pipex_init(&pipex, envp);
	ft_parse(&pipex, av, ac);
	pipex.cmd_nbr = ac - 2 - pipex.here_doc;
	pipex.pids = malloc(sizeof(pid_t) * (pipex.cmd_nbr));
	if (!pipex.pids)
		free_pipex(&pipex, -1, "pipex: malloc: %s\n", strerror(errno));
	if (ac > 3)
		while (++pipex.i < pipex.cmd_nbr)
			child_process(&pipex, av[pipex.i + 1 + pipex.here_doc], envp);
	else
		while (++pipex.i < pipex.cmd_nbr)
			exec_one(&pipex, av[pipex.i + 1 + pipex.here_doc], envp);
	while (++pipex.i_wait < pipex.cmd_nbr)
		waitpid(pipex.pids[pipex.i_wait], &pipex.status, 0);
	free_pipex(&pipex, -1, NULL, NULL);
	if (WIFEXITED(pipex.status))
		return (WEXITSTATUS(pipex.status));
	return (pipex.status);
}

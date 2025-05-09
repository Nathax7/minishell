/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/09 17:04:44 by nagaudey         ###   ########.fr       */
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

void	ft_parse(t_exec *exec, char **av, int ac)
{
	// if (ft_strncmp(av[0], "here_doc", 8) == 0)
	// {
	// 	if (ac < 5)
	// 	{
	// 		exec->exec->pipex.here_doc = 0;
	// 		free_parent(exec, -1, NULL, NULL);
	// 		usage();
	// 	}
	if (exec->pipex.append == 1)
	{
		open_infile(exec, av[0]);
		open_outfile(exec, av[ac - 1], 0);
	}
	else
	{
		exec->pipex.here_doc = 0;
		open_infile(exec, av[0]);
		open_outfile(exec, av[ac - 1], 1);
	}
}

int	pipex(t_exec *exec, int ac, char **av, char **envp)
{
	if (ac < 3)
		return (usage());
	pipex_init(exec, envp);
	ft_parse(exec, av, ac);
	exec->pipex.cmd_nbr = ac - 2 - exec->pipex.here_doc;
	exec->pipex.pids = malloc(sizeof(pid_t) * (exec->pipex.cmd_nbr));
	if (!exec->pipex.pids)
		free_pipex(exec, -1, "pipex: malloc: %s\n", strerror(errno));
	if (ac > 3)
		while (++exec->pipex.i < exec->pipex.cmd_nbr)
			child_process(exec, av[exec->pipex.i + 1 + exec->pipex.here_doc],
				envp);
	else
		while (++exec->pipex.i < exec->pipex.cmd_nbr)
			exec_one(exec, av[exec->pipex.i + 1 + exec->pipex.here_doc], envp);
	while (++exec->pipex.i_wait < exec->pipex.cmd_nbr)
		waitpid(exec->pipex.pids[exec->pipex.i_wait], &exec->pipex.status, 0);
	// free_pipex(exec, -1, NULL, NULL);
	if (WIFEXITED(exec->pipex.status))
		return (WEXITSTATUS(exec->pipex.status));
	return (exec->pipex.status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 00:01:49 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/14 18:42:42 by nagaudey         ###   ########.fr       */
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

void	ft_parse(t_exec *exec)
{
	// if (ft_strncmp(av[0], "here_doc", 8) == 0)
	// {
	// 	if (ac < 5)
	// 	{
	// 		exec->exec->pipex.here_doc = 0;
	// 		free_parent(exec, -1, NULL, NULL);
	// 		usage();
	// 	}
	if (exec->append[exec->i] == 1)
	{
		if (exec->infile_name[exec->i] != NULL)
			open_infile(exec, exec->infile_name[exec->i]);
		if (exec->outfile_name[exec->i] != NULL)
			open_outfile(exec, exec->outfile_name[exec->i], 0);
	}
	else
	{
		if (exec->infile_name[exec->i] != NULL)
			open_infile(exec, exec->infile_name[exec->i]);
		if (exec->outfile_name[exec->i] != NULL)
			open_outfile(exec, exec->outfile_name[exec->i], 1);
	}
}

int	pipex(t_exec *exec, int ac, char **av, char **envp)
{
	if (ac < 1)
		return (usage());
	pipex_init(exec, envp);
	exec->pipex.cmd_nbr = ac;
	ft_parse(exec);
	exec->pipex.pids = malloc(sizeof(pid_t) * ac);
	if (!exec->pipex.pids)
		free_pipex(exec, -1, "pipex: malloc: %s\n", strerror(errno));
	if (ac > 1)
		while (++exec->pipex.i < ac)
			child_process(exec, av[exec->pipex.i], envp);
	else
		while (++exec->pipex.i < ac)
			exec_one(exec, av[exec->pipex.i], envp);
	while (++exec->pipex.i_wait < ac)
		waitpid(exec->pipex.pids[exec->pipex.i_wait], &exec->pipex.status, 0);
	// free_pipex(exec, -1, NULL, NULL);
	if (WIFEXITED(exec->pipex.status))
		return (WEXITSTATUS(exec->pipex.status));
	return (exec->pipex.status);
}

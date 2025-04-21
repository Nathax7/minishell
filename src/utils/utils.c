/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:58:31 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/21 21:59:45 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	usage(void)
{
	ft_putstr_fd("\033[31mError: Bad argument\n\e[0m", 2);
	ft_putstr_fd("Ex: ./minishell <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./minishell \"here_doc\" <LIMITER> <cmd> <cmd1>"
		"<...> <file>\n", 1);
	exit(EXIT_FAILURE);
}

// void	minishell_init(t_cmd *cmd, char **envp)
// {
// 	size_t	i;

// 	*cmd = (t_cmd){0};
// 	cmd->infile = -1;
// 	cmd->outfile = -1;
// 	cmd->here_doc = 1;
// 	cmd->env = 1;
// 	i = 0;
// 	while (envp && envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
// 		i++;
// 	if (!envp || !envp[i])
// 	{
// 		cmd->env = 0;
// 		return ;
// 	}
// 	cmd->paths = ft_split(envp[i] + 5, ':');
// 	if (!cmd->paths)
// 		if (errno == ENOMEM)
// 			msg_utils(NULL, "Error malloc");
// }

void	open_infile(t_cmd *cmd, char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		free_cmd(cmd, 1, NULL, infile);
	}
	if (access(infile, R_OK) == -1)
	{
		free_cmd(cmd, 1, NULL, infile);
		return ;
	}
	cmd->infile = open(infile, O_RDONLY);
	if (cmd->infile == -1)
		free_cmd(cmd, 1, NULL, "Error open infile");
}

void	open_outfile(t_cmd *cmd, char *outfile, int mode)
{
	if (access(outfile, F_OK) == 0)
	{
		if (access(outfile, W_OK) == -1)
			free_cmd(cmd, 1, NULL, outfile);
	}
	if (mode == 0)
		cmd->outfile = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)
		cmd->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->outfile == -1)
		free_cmd(cmd, 1, NULL, "Error open outfile");
}


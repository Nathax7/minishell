/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 23:55:48 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/08 15:16:02 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/all.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define CHARSET "abcdefghijklmnopqrstuvwxyz"

typedef struct s_pipex
{
	pid_t	*pids;
	char	*cmd;
	char	**cmd_args;
	char	**paths;
	char	*path;
	int		infile;
	int		outfile;
	char	*infile_name;
	char	*outfile_name;
	int		fd[2];
	int		status;
	int		here_doc;
	int		cmd_nbr;
	int		i_wait;
	int		i;
	int		envp;
}			t_pipex;

void		pipex_init(t_pipex *pipex, char **envp);
void		free_parent(t_pipex *pipex, int status, char *str, char *arg);
void		random_filename(t_pipex *pipex);
void		open_infile(t_pipex *pipex, char *argv);
void		open_outfile(t_pipex *pipex, char *argv, int mode);
void		here_doc(t_pipex *pipex, char *limiter);
void		usage(void);
void		child_process(t_pipex *pipex, char *argv, char **envp);
void		execute_bonus(t_pipex *pipex, char *argv, char **envp);

#endif
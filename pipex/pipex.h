/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:56:29 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/08 15:03:07 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/all.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		filein;
	int		fileout;
	int		type;
	int		status;
	pid_t	*pids;
	int		count;
	int		flag;
}			t_pipex;

void		execute(char *argv, char **envp);
void		execute_bonus(t_pipex *pipex, char *argv, char **envp);
void		usage(void);
void		ft_free_double(char **str);
char		*find_path(char *cmd, char **envp);

#endif
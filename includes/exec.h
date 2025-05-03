/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/03 17:18:16 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"

void	free_pipex(t_pipex *pipex, int status, char *str, char *str2);
void	ft_message(char *str, char *str2);
void	init_file(t_pipex *pipex, t_type type);
int		exec(char **envp, int cmd_nbr, char **line);
void	free_triple(char ***triple);
void	free_exec(t_exec *exec);
void	split_pipeline_groups(t_exec *exec, char **tokens);
void	child_process(t_pipex *pipex, char *argv, char **envp);
void	here_doc(t_pipex *pipex, char *limiter);
void	free_parent(t_pipex *pipex, int status, char *str, char *arg);
void	pipex_init(t_pipex *pipex, char **envp);
void	open_infile(t_pipex *pipex, char *infile);
void	open_outfile(t_pipex *pipex, char *outfile, int mode);
void	execute_bonus(t_pipex *pipex, char *argv, char **envp);
int		pipex(int ac, char **av, char **envp);
void	exec_one(t_pipex *pipex, char *argv, char **envp);
void	random_filename(t_pipex *pipex);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 15:25:13 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"

void	free_pipex(t_pipex *pipex, int status, char *str, char *str2);
void	free_exec(t_exec *exec, int status, char *str, char *str2);
void	ft_message(char *str, char *str2);
void	free_triple(char ***triple);
void	split_pipeline_groups(t_exec *exec, char **tokens);
void	child_process(t_pipex *pipex, char *argv, char **envp);
void	here_doc(t_pipex *pipex, char *limiter);
void	pipex_init(t_pipex *pipex, char **envp);
void	execute_bonus(t_pipex *pipex, char *argv, char **envp);
int		pipex(int ac, char **av, char **envp);
void	exec_one(t_pipex *pipex, char *argv, char **envp);
void	random_filename(t_pipex *pipex);

#endif
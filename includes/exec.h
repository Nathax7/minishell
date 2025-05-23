/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/23 10:21:33 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"

void	free_pipex(t_exec *exec, int status, char *str, char *str2);
void	free_exec(t_exec *exec, int status, char *str, char *str2);
void	ft_message(char *str, char *str2);
void	free_triple(char ***triple);
t_exec	*split_pipeline_groups(t_token *tokens);
void	child_process(t_exec *exec, char *argv, char **envp);
void	here_doc(t_exec *exec, char *limiter);
void	pipex_init(t_exec *exec, char **envp);
void	execute_bonus(t_exec *exec, char *argv, char **envp);
int		pipex(t_exec *exec, int ac, char **av, char **envp);
void	exec_one(t_exec *exec, char *argv, char **envp);
void	random_filename(t_exec *exec);


#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:46:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/29 20:08:47 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"
# include "utils.h"

void	free_triple(char ***triple);
void	child_process(t_exec *exec, int cmd_index, char **envp);
char	*here_doc(t_files *files, char *limiter);
void	find_path(t_exec *exec, char *cmd);
void	execute_bonus(t_exec *exec, char **envp);
int		pipex(t_token *tokens, char **envp);
void	exec_one(t_exec *exec, char **envp);
int		open_here_doc(t_files *files);
void	struct_open_infile(t_exec *exec);
void	struct_open_outfile(t_exec *exec);
int		random_filename(t_files *files);
t_cmd	*parsing_cmd(t_token *tokens);
void	parsing_exec(t_token *tokens, t_exec *exec);
void	exec_init(t_exec *exec, char **envp);
void	free_cmd_list(t_cmd *cmd_list, int is_parent);
int		is_builtin(t_exec *exec, char **envp);
int		is_directory(t_exec *exec);
void	setup_pipe_redirections(t_exec *exec, int cmd_index);
void	execute_child(t_exec *exec, int cmd_index, char **envp);
int		execute_single_builtin_in_parent(t_exec *exec, char **envp);
void	process_redirections_in_order(t_exec *exec);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:46:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/08/16 19:34:54 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtins.h"
# include "signals.h"
# include "utils.h"

void	child_process(t_exec *exec, int cmd_index, char **envp);
char	*here_doc(t_files *files, char *limiter);
void	find_path(t_exec *exec, char *cmd);
void	ft_execute(t_exec *exec, char **envp);
int		exec(t_token *tokens, char ***envp_ptr);
int		open_here_doc(t_files *files);
void	struct_open_infile(t_exec *exec);
void	struct_open_outfile(t_exec *exec);
int		random_filename(t_files *files);
t_cmd	*parsing_cmd(t_token *tokens, char ***envp_ptr);
void	parsing_exec(t_token *tokens, t_exec *exec, char ***envp_ptr);
void	exec_init(t_exec *exec, char **envp);
void	free_cmd_list(t_cmd *cmd_list, int is_parent);
int		execute_builtin(t_exec *exec, char ***envp_ptr);
int		execute_builtin_in_child(t_exec *exec, char **envp);
int		is_builtin(t_args *cmd);
int		is_directory(t_exec *exec);
void	setup_pipe_redirections(t_exec *exec, int cmd_index);
void	execute_child(t_exec *exec, int cmd_index, char **envp);
int		execute_single_builtin_in_parent(t_exec *exec, char ***envp_ptr);
t_files	*new_outfile_node(char *value, int append);
t_files	*new_infile_node(char *value, int heredoc, char ***envp_ptr);
t_cmd	*append_cmd_node(t_cmd *node);
t_args	*append_args_node(t_args *current, char *value);

#endif
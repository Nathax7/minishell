/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:46:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/17 18:00:06 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"

void	ft_message(char *str, char *str2);
void	free_triple(char ***triple);
void	child_process(t_exec *exec, int cmd_index, char **envp);
char	*here_doc(t_files *files, char *limiter);
void	find_path(t_exec *exec, char *cmd);
void	execute_bonus(t_exec *exec, char **envp);
int		pipex(t_token *tokens, char **envp);
void	exec_one(t_exec *exec, char **envp);
void	open_infile(t_exec *exec, int previous_fd);
void	open_outfile(t_exec *exec, int previous_fd);
int	open_here_doc(t_files *files);
void	struct_open_infile(t_exec *exec);
void	struct_open_outfile(t_exec *exec);
int	random_filename(t_files *files);
t_cmd	*parsing_cmd(t_token *tokens);
void parsing_exec(t_token *tokens, t_exec *exec);
void	exec_init(t_exec *exec, char **envp);
void	free_child(t_exec *exec, int status, char *str, char *str2);
void	free_parent(t_exec *exec, int status, char *str, char *str2);
void	free_cmd_list(t_cmd *cmd_list, int is_parent);
void	print_cmd_list_detailed(t_cmd *cmd_list);

#endif
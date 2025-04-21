/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/21 23:54:24 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"

void	free_cmd(t_cmd *cmd, int status, char *str, char *str2);
void	ft_message(char *str, char *str2);
void	init_path(t_cmd *cmd, char **envp);
void	init_file(t_cmd *cmd);
void	execute(t_cmd *cmd, char **envp);
void	child_process(t_cmd *cmd, char **envp);
int		exec(t_cmd *cmd, int cmd_nbr, char **envp);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/19 19:28:57 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "utils.h"

void	free_parent_cmd(t_cmd *cmd, int status, char *str, char *str2);
void	msg_cmd(char *str, char *str2);
void	is_here_doc(t_cmd *cmd, char **av, int ac);
void	execute(t_cmd *cmd, char *argv, char **envp);
void	msg_utils(char *str, char *str2);
void	free_parent_utils(t_cmd *utils, int status, char *str, char *str2);

#endif
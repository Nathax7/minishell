/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/10 16:03:10 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "struct.h"
#include "utils.h"

void	free_parent_cmd(t_cmd *cmd, int status, char *str, char *str2);
void	msg_cmd(char *str, char *str2);
void	is_here_doc(t_cmd *cmd, char **av, int ac);
void	execute(t_cmd *cmd, char *argv, char **envp);

#endif
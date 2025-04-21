/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/21 20:56:09 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "utils.h"

void	free_cmd(t_cmd *cmd, int status, char *str, char *str2);
void	ft_message(char *str, char *str2);
void	init_cmd(t_cmd *cmd, char **envp);
void	execute(t_cmd *cmd, char **envp);
void	child_process(t_cmd *cmd, char **envp);

#endif
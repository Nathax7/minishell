/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:12:21 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/23 18:43:22 by nagaudey         ###   ########.fr       */
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
char	***split_pipeline_groups(char **tokens);

#endif
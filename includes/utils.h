/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:07:53 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/21 18:41:22 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	minishell_init(t_cmd *cmd, char **envp);
void	open_infile(t_cmd *cmd, char *infile);
void	open_outfile(t_cmd *cmd, char *outfile, int mode);
void	usage(void);
// void	delete_list(t_node *head);
// void	delete_list_exit(t_node *head);
void	free_token(t_token *token, int status, char *str, char *str2);
void	free_cmd(t_cmd *cmd, int status, char *str, char *str2);
void	free_cmd_list(t_cmd *lst);
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstlast(t_cmd *lst);
void ft_close(t_cmd *cmd, t_type type);

#endif
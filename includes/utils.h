/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:07:53 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/02 17:54:42 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	minishell_init(t_pipex *pipex, char **envp);
void	open_infile(t_pipex *pipex, char *infile);
void	open_outfile(t_pipex *pipex, char *outfile, int mode);
void	usage(void);
void	free_split(char **arr);
void	free_triple(char ***triple);
// void	delete_list(t_node *head);
// void	delete_list_exit(t_node *head);
void	free_token(t_token *token, int status, char *str, char *str2);
void	free_pipex(t_pipex *pipex, int status, char *str, char *str2);
void	free_pipex_list(t_pipex *lst);
void	ft_lstadd_back(t_pipex **lst, t_pipex *new);
t_pipex	*ft_lstlast(t_pipex *lst);
void ft_close(t_pipex *pipex, t_type type);

#endif
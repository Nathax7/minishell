/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:46:54 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/27 21:47:03 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	ft_message(char *str, char *str2);
void	open_infile(t_exec *exec, char *infile);
void	open_outfile(t_exec *exec, char *outfile, int mode);
int		usage(void);
void	free_split(char **arr);
void	free_triple(char ***triple);
void	free_token(t_token *token, int status, char *str, char *str2);
void	free_pipex(t_exec *exec, int status, char *str, char *str2);
void	free_pipex_core(t_exec *exec);
void	ft_close(t_exec *exec, t_type type);
void	free_exec(t_exec *exec, int status, char *str, char *str2);
t_exec *free_exec_list(t_exec *exec, char *str, char *str2);
void	open_infile(t_exec *exec, char *infile);
int	open_infile_exec(t_exec *exec, char *infile);
void	open_outfile(t_exec *exec, char *outfile, int mode);
int	open_outfile_exec(t_exec *exec, char *outfile, int mode);
t_exec	*find_last(t_exec *lst);
t_exec	*find_first(t_exec *lst);
int		find_size(t_token *lst);
char	*ft_strjoin_space(char const *s1, char const *s2);
#endif
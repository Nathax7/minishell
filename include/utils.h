/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:07:53 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/10 15:53:07 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	minishell_init(t_cmd *cmd, char **envp);
void	open_infile(t_cmd *cmd, char *infile);
void	open_outfile(t_cmd *cmd, char *outfile, int mode);
void	usage(void);
void	delete_list(t_node *head);
void	*ft_malloc(size_t size, t_node **head);

#endif
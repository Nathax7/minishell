/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 20:58:31 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 15:36:17 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"


// void	minishell_init(t_cmd *cmd, char **envp)
// {
// 	size_t	i;

// 	*cmd = (t_cmd){0};
// 	cmd->infile = -1;
// 	cmd->outfile = -1;
// 	cmd->here_doc = 1;
// 	cmd->env = 1;
// 	i = 0;
// 	while (envp && envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
// 		i++;
// 	if (!envp || !envp[i])
// 	{
// 		cmd->env = 0;
// 		return ;
// 	}
// 	cmd->paths = ft_split(envp[i] + 5, ':');
// 	if (!cmd->paths)
// 		if (errno == ENOMEM)
// 			msg_utils(NULL, "Error malloc");
// }



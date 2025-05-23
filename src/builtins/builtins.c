/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:33:04 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/23 17:57:26 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **args, char ***env_ptr)
{
	if (!args || !args[0])
		return (-1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, env_ptr));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args, env_ptr));
	else if (ft_strcmp(args[0], "") == 0)
		return (builtin_(args, env_ptr));
	return (-1);
}

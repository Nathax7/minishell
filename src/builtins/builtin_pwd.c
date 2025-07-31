/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/28 16:35:06 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_pwd(t_args *args)
{
	char	*pwd;

	if (args && args->next && args->next->cmd_args
		&& args->next->cmd_args[0] == '-')
	{
		ft_putstr_fd("minishell: pwd: -", 2);
		ft_putchar_fd(args->next->cmd_args[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	free(pwd);
	return (0);
}

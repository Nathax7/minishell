/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:58:59 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/28 16:34:50 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_argument(t_args *args)
{
	if (args && args->next && args->next->cmd_args
		&& args->next->cmd_args[0] != '-')
	{
		ft_putstr_fd("env: arguments not accepted\n", 2);
		return (1);
	}
	return (0);
}

int	is_option(t_args *args)
{
	if (args && args->next && args->next->cmd_args
		&& args->next->cmd_args[0] == '-')
	{
		ft_putstr_fd("env: invalid option -- '", 2);
		ft_putchar_fd(args->next->cmd_args[1], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

int	builtin_env(t_args *args, char ***env_ptr)
{
	char	**envp;
	int		i;

	if (is_option(args))
		return (2);
	if (is_argument(args))
		return (2);
	if (!env_ptr || !*env_ptr)
		return (1);
	envp = *env_ptr;
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
		{
			ft_putstr_fd(envp[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		i++;
	}
	return (0);
}

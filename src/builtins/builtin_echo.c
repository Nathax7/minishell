/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:48:04 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/19 19:00:01 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	is_valid_n_flag(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	if (arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_args *args)
{
	int	newline;

	if (!args)
		return (1);

	newline = 1;
	args = args->next;
	while (args && args->cmd_args && is_valid_n_flag(args->cmd_args))
	{
		newline = 0;
		args = args->next;
	}
	while (args && args->cmd_args)
	{
		ft_putstr_fd(args->cmd_args, STDOUT_FILENO);
		if (args->next && args->next->cmd_args)
			ft_putchar_fd(' ', STDOUT_FILENO);
		args = args->next;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

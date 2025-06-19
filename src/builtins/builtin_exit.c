/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:56:30 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/19 16:34:35 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	is_numeric_string(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_args *args)
{
	int exit_code;

	ft_putstr_fd("exit\n", STDERR_FILENO);

	if (!args->next->cmd_args)
		exit(0);
	if (!is_numeric_string(args->next->cmd_args))
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(args->next->cmd_args, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	if (args->next->next->cmd_args)
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atoi(args->next->cmd_args);
	exit(exit_code & 255);

}

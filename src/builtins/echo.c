/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:48:04 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/02 15:40:31 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

int	builtin_echo(char **args)
{
	int i;

	if (!args || !*args)
		return (1);
	if (args[1] && args[1][0] == '-' && args[1][1] == 'n' && args[1][2] == '\0')
		i = 2;
	else
		i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (args[1] && (!(args[1][0] == '-' && args[1][1] == 'n' && args[1][2] == '\0')))
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messaging_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:12:09 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/29 19:05:31 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	ft_message(char *command, char *arg, char *error)
{
	int	use_quotes;

	use_quotes = 0;
	if (command && ft_strcmp(command, "export") == 0 && error
		&& ft_strstr(error, "not a valid identifier"))
		use_quotes = 1;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (command)
	{
		ft_putstr_fd(command, STDERR_FILENO);
		if (arg || error)
			ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		if (use_quotes)
			ft_putchar_fd('`', STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		if (use_quotes)
			ft_putchar_fd('\'', STDERR_FILENO);
		if (error)
			ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (error)
		ft_putstr_fd(error, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

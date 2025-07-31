/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:12:09 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/24 14:13:45 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	ft_message(char *command, char *arg, char *error)
{
	int	use_quotes;

	use_quotes = (command && ft_strcmp(command, "export") == 0 && error
			&& ft_strstr(error, "not a valid identifier"));
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

int	ft_return_message(char *command, char *arg, char *error, int status)
{
	ft_message(command, arg, error);
	return (status);
}

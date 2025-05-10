/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:42:23 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/10 22:56:52 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	display_error(const char *context, const char *msg, int print_perror)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (context)
	{
		ft_putstr_fd((char *)context, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	if (print_perror)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	g_exit_status = 1; // Adopte le statut d'erreur general
}

void	report_syntax_error(const char *near_token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (near_token)
		ft_putstr_fd((char *)near_token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO); // Pour les erreurs d'EOL
	ft_putstr_fd("'\n", STDERR_FILENO);
	g_exit_status = 2; // Bash utilise 2 pr les err de syntaxe
}

void	report_syntax_error_detail(const char *message, const char *detail)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)message, STDERR_FILENO);
	if (detail)
	{
		ft_putstr_fd(" `", STDERR_FILENO);
		ft_putstr_fd((char *)detail, STDERR_FILENO);
		ft_putstr_fd("'", STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
	g_exit_status = 2;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:42:23 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/06 16:26:21 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	report_syntax_error(const char *near_token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (near_token)
		ft_putstr_fd((char *)near_token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	handle_syntax_error(t_syntax_result *result)
{
	if (result->error_token)
	{
		report_syntax_error(result->error_token);
		free(result->error_token);
		result->error_token = NULL;
	}
	if (result->tokens)
	{
		free_token_list(result->tokens);
		result->tokens = NULL;
	}
}
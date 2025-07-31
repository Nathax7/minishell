/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:42:23 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/25 12:05:23 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

void	report_syntax_error(char *near_token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token",
		STDERR_FILENO);
	if (near_token)
	{
		ft_putstr_fd(" `", STDERR_FILENO);
		ft_putstr_fd((char *)near_token, STDERR_FILENO);
	}
	else
		ft_putstr_fd("`newline", STDERR_FILENO);
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
}

void	*cleanup_parsing_and_return_null(t_syntax_result *result,
		char *error_msg)
{
	if (error_msg)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	if (result)
	{
		if (result->tokens)
		{
			free_token_list(result->tokens);
			result->tokens = NULL;
		}
		if (result->expanded_tokens)
		{
			free_token_list(result->expanded_tokens);
			result->expanded_tokens = NULL;
		}
		if (result->error_token)
		{
			free(result->error_token);
			result->error_token = NULL;
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:35:07 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/08 11:32:46 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_parse_result	handle_syntax_success(t_syntax_result *result, char **envp,
		int *exit_status)
{
	result->expanded_tokens = process_complete_syntax(*result, envp,
			exit_status);
	result->tokens = NULL;
	if (result->expanded_tokens)
		return (PARSE_SUCCESS);
	return (PARSE_ERROR);
}

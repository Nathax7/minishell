/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:21:49 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/28 16:35:45 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	init_parser_context(t_parser_context *ctx, t_token *tokens,
		t_syntax_result *result)
{
	ctx->current = tokens;
	ctx->state = STATE_START;
	ctx->has_command = 0;
	ctx->result = result;
}

void	set_syntax_error(t_parser_context *ctx, const char *token_val)
{
	ctx->result->status = PARSE_SYNTAX_ERROR;
	ctx->result->error_token = ft_strdup(token_val ? token_val : "newline");
	ctx->result->next_prompt = PROMPT_MAIN;
}

void	set_incomplete_status(t_parser_context *ctx, t_parse_status status,
		t_prompt_type prompt)
{
	ctx->result->status = status;
	ctx->result->next_prompt = prompt;
	ctx->result->error_token = NULL;
}
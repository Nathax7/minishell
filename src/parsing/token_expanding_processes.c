/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expanding_processes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:50:04 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/29 17:53:36 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	process_heredoc_word(t_token *current, t_token **expanded_head)
{
	char	*op_copy;

	op_copy = ft_strdup(current->value);
	if (!op_copy || !create_and_append_token(expanded_head,
			op_copy, current->type, current->quote))
		return (0);
	return (1);
}

int	process_regular_word(t_token *current, t_token **expanded_head,
	t_expand_context *ctx)
{
	return (process_word_expansion(current, expanded_head, ctx->envp,
			ctx->exit_status));
}

int	process_word_token(t_token *current, t_token *prev,
	t_token **expanded_head, t_expand_context *ctx)
{
	if (prev && prev->type == T_HEREDOC)
		return (process_heredoc_word(current, expanded_head));
	else
		return (process_regular_word(current, expanded_head, ctx));
}

int	process_non_word_token(t_token *current, t_token **expanded_head)
{
	char	*op_copy;

	op_copy = ft_strdup(current->value);
	if (!op_copy || !create_and_append_token(expanded_head, op_copy,
			current->type, Q_NONE))
		return (0);
	return (1);
}

int	process_single_token(t_token *current, t_token *prev,
	t_token **expanded_head, t_expand_context *ctx)
{
	if (current->type == T_WORD)
		return (process_word_token(current, prev, expanded_head, ctx));
	else
		return (process_non_word_token(current, expanded_head));
}

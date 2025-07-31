/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:11:15 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/31 13:39:06 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*expand_token_value(const char *value, t_quote quote_type, char **envp,
		int exit_status)
{
	if (quote_type == Q_SINGLE)
		return (ft_strdup(value));
	return (expand_variables_in_str(value, envp, exit_status));
}

int	should_field_split(t_quote quote_type)
{
	return (quote_type == Q_NONE);
}

t_token	*expand_tokens(t_token *tokens, char **envp, int exit_status)
{
	t_token				*current;
	t_token				*expanded_head;
	t_token				*prev;
	t_expand_context	ctx;

	ctx.envp = envp;
	ctx.exit_status = exit_status;
	expanded_head = NULL;
	current = tokens;
	prev = NULL;
	while (current)
	{
		if (!process_single_token(current, prev, &expanded_head, &ctx))
			return (free_token_list_and_return_null(expanded_head));
		prev = current;
		current = current->next;
	}
	return (expanded_head);
}

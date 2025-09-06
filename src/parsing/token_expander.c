/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 18:11:15 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/19 17:57:12 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	should_expand_variable(char current_char, char next_char)
{
	if (current_char != '$')
		return (0);
	if (is_valid_var_char(next_char) || next_char == '?' || next_char == '{')
		return (1);
	return (0);
}

t_token	*expand_tokens(t_token *tokens, char **envp, int *exit_status)
{
	t_token				*current;
	t_token				*expanded_head;
	t_token				*prev;
	t_expand_context	ctx;

	ctx.envp = envp;
	ctx.exit_status = *exit_status;
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

int	process_regular_char(t_str_builder *sb, const char **ip)
{
	if (!sb_append_char(sb, **ip))
		return (0);
	(*ip)++;
	return (1);
}

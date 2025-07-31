/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_quoting_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:40:41 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/31 13:36:05 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "utils.h"

int	handle_quote_start(t_str_builder *sb, const char **ip,
		char *current_quote)
{
	*current_quote = **ip;
	if (!sb_append_char(sb, **ip))
		return (0);
	(*ip)++;
	return (1);
}

int	handle_quote_end(t_str_builder *sb, const char **ip,
		char *current_quote)
{
	if (!sb_append_char(sb, **ip))
		return (0);
	*current_quote = 0;
	(*ip)++;
	return (1);
}

int	handle_single_quote(t_str_builder *sb, const char **ip)
{
	if (!sb_append_char(sb, **ip))
		return (0);
	(*ip)++;
	return (1);
}

int	handle_double_quote_escape(t_str_builder *sb, const char **ip)
{
	(*ip)++;
	if (!sb_append_char(sb, **ip))
		return (0);
	(*ip)++;
	return (1);
}

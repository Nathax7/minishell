/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:26:06 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/09 17:26:08 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

t_token_type	identify_redirect(const char *s, int *i, int flag)
{
	if (flag)
	{
		if (s[*i + 1] == '<')
		{
			type = T_HEREDOC;
			(*i) = (*i) + 2;
		}
		else
		{
			type = T_REDIRECT_IN;
			(*i) = (*i) + 1;
		}
	}
	else
	{
		if (s[*i + 1] == '>')
		{
			type = T_APPEND;
			(*i) = (*i) + 2;
		}
		else
		{
			type = T_REDIRECT_OUT;
			(*i) = (*i) + 1;
		}
	}
	return (type);
}


t_token_type	identify_operator(const char *s, int *i)
{
	t_token_type type;

	type = T_WORD;
	if (s[*i] == '|')
	{
		type = T_PIPE;
		(*i) = (*i) + 1;
	}
	else if (s[*i] == '<')
		type = identify_redirect(s, i, 1, type);
	else if (s[*i] == '>')
		type = identify_redirect(s, i, 0, type);
	return (type);
}
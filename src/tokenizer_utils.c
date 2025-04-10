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

#include "../inc/parsing.h"

t_token_type	identify_redirect(const char *s, int *i, int flag)
{
	if (flag)
	{
		if (s[*i + 1] == '<')
		{
			(*i) = (*i) + 2;
			return(T_HEREDOC);
		}
		(*i) = (*i) + 1;
		return(T_REDIRECT_IN);
	}
	else
	{
		if (s[*i + 1] == '>')
		{
			(*i) = (*i) + 2;
			return(T_APPEND);
		}
		(*i) = (*i) + 1;
		return(T_REDIRECT_OUT);
	}
}

t_token_type	identify_operator(const char *s, int *i)
{
	if (s[*i] == '|')
	{
		(*i) = (*i) + 1;
		return(T_PIPE);
	}
	else if (s[*i] == '<')
		return (identify_redirect(s, i, 1));
	else if (s[*i] == '>')
		return (identify_redirect(s, i, 0));
	return (T_WORD);
}

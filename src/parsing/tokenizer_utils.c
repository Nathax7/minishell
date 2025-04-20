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

#include "../../includes/parsing.h"

t_token_type	identify_redirect(const char *s, int *i, int flag)
{
	if (flag)
	{
		if (s[*i + 1] == '<')
		{
			(*i) = (*i) + 2;
			return (T_HEREDOC);
		}
		(*i) = (*i) + 1;
		return (T_REDIRECT_IN);
	}
	else
	{
		if (s[*i + 1] == '>')
		{
			(*i) = (*i) + 2;
			return (T_APPEND);
		}
		(*i) = (*i) + 1;
		return (T_REDIRECT_OUT);
	}
}

t_token_type	identify_operator(const char *s, int *i)
{
	if (s[*i] == '|')
	{
		(*i) = (*i) + 1;
		return (T_PIPE);
	}
	else if (s[*i] == '<')
		return (identify_redirect(s, i, 1));
	else if (s[*i] == '>')
		return (identify_redirect(s, i, 0));
	return (T_WORD);
}

/* determine si le mot est 'mot' ou "mot" */
static t_quote	get_quote_kind(const char *s, int start, int end)
{
	if (end - start >= 2 && s[start] == '\'' && s[end - 1] == '\'')
		return (Q_SINGLE);
	if (end - start >= 2 && s[start] == '"' && s[end - 1] == '"')
		return (Q_DOUBLE);
	return (Q_NONE);
}

/* IDENTIFY WORD - savoir si c'est un mot ET type de quote */
char	*identify_word(const char *str, int *i, t_quote *qk)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (str[*i] && !ft_strchr(" \t|<>", str[*i]))
	{
		if ((str[*i] == '\'' || str[*i] == '"') && !quote)
			quote = str[*i];
		else if (quote && str[*i] == quote)
			quote = 0;
		(*i)++;
	}
	*qk = get_quote_kind(str, start, *i);
	return (ft_substr(str, start, *i - start));
}

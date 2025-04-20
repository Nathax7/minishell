/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:14:42 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 14:35:04 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static void	add_token4(t_token **lst, char *val, t_token_type ty, t_quote qk)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof *new);
	if (!new)
		return ;
	new->value = val;
	new->type = ty;
	new->quote = qk;
	new->next = NULL;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*tokenize(char *argument)
{
	t_token			*tokens;
	int				i;
	t_token_type	type;

	tokens = NULL;
	i = 0;
	t_quote quote_type; /* mon nathax ou miel */
	while (argument[i])
	{
		while (argument[i] && ft_strchr(" \t", argument[i]))
			i++;
		if (!argument[i])
			break ;
		if (is_operator(argument[i]))
		{
			type = identify_operator(argument, &i);
			if (type == T_HEREDOC)
				add_token4(&tokens, ft_strdup("<<"), type, Q_NONE);
			else if (type == T_APPEND)
				add_token4(&tokens, ft_strdup(">>"), type, Q_NONE);
			else if (type == T_REDIRECT_IN)
				add_token4(&tokens, ft_strdup("<"), type, Q_NONE);
			else if (type == T_REDIRECT_OUT)
				add_token4(&tokens, ft_strdup(">"), type, Q_NONE);
			else /* si c'est un T_PIPE du coup */
				add_token4(&tokens, ft_strdup("|"), type, Q_NONE);
		}
		else
			add_token4(&tokens, identify_word(argument, &i, &quote_type),
				T_WORD, quote_type);
	}
	return (tokens);
}

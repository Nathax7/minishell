/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mimoulapinou <bebefripouille@chaton.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:14:42 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/12 12:48:39 by Mimoulapino      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*identify_word(const char *str, int *i)
{
	int		start;
	char	quote;

	start = *i;
	while (str[*i] && !ft_strchr(" \t|<>", str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			quote = str[*i];
			(*i) = (*i) + 1;
			while (str[*i] && str[*i] != quote)
				(*i) = (*i) + 1;
			if (str[*i] == quote)
				(*i) = (*i) + 1;
		}
		else
			(*i) = (*i) + 1;
	}
	return (strndup(&str[start], *i - start));
}

void	add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	new->value = value;
	new->type = type;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*tokenize(char *argument)
{
	t_token	*tokens;
	int		i;
	t_token_type type;

	tokens = NULL;
	i = 0;
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
				add_token(&tokens, strdup("<<"), type);
			else if (type == T_APPEND)
				add_token(&tokens, strdup(">>"), type);
			else if (type == T_REDIRECT_IN)
				add_token(&tokens, strdup("<"), type);
			else if (type == T_REDIRECT_OUT)
				add_token(&tokens, strdup(">"), type);
			else if (type == T_PIPE)
				add_token(&tokens, strdup("|"), type);
		}
		else
			add_token(&tokens, identify_word(argument, &i), T_WORD);
	}
	return (tokens);
}


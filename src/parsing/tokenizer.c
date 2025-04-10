/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:14:42 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/09 18:25:28 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_type	identify_operator(const char *s, int *i)
{
	if (s[*i] == '|')
	{
		(*i)++;
		return (TOKEN_PIPE);
	}
	if (s[*i] == '<')
	{
		if (s[*i + 1] == '<')
		{
			(*i) += 2;
			return (TOKEN_HEREDOC);
		}
		(*i)++;
		return (TOKEN_REDIRECT_IN);
	}
	if (s[*i] == '>')
	{
		if (s[*i + 1] == '>')
		{
			(*i) += 2;
			return (TOKEN_APPEND);
		}
		(*i)++;
		return (TOKEN_REDIRECT_OUT);
	}
	return (-1);
}

char	*identify_word(const char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '\t'
		&& str[*i] != '|' && str[*i] != '<' && str[*i] != '>')
	{
		(*i)++;
	}
	return (strndup(&str[start], *i - start));
}

void	add_token(t_token **head, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = malloc(sizeof(t_token));
	if (!new)
		return ; // handle malloc fail later
	new->value = value;
	new->type = type;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_token	*tokenize(char *input)
{
	t_token			*tokens;
	int				i;
	t_token_type	type;
	char			*op_value;
	char			*word;

	tokens = NULL;
	i = 0;
	while (input[i] != '\0')
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\0')
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			type = identify_operator(input, &i);
			if (type == TOKEN_PIPE)
				op_value = strdup("|");
			else if (type == TOKEN_REDIRECT_IN)
				op_value = strdup("<");
			else if (type == TOKEN_REDIRECT_OUT)
				op_value = strdup(">");
			else if (type == TOKEN_APPEND)
				op_value = strdup(">>");
			else if (type == TOKEN_HEREDOC)
				op_value = strdup("<<");
			else
				continue ;
			add_token(&tokens, op_value, type);
		}
		else
		{
			word = identify_word(input, &i);
			add_token(&tokens, word, TOKEN_WORD);
		}
	}
	return (tokens);
}

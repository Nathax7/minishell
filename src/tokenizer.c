/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:14:42 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/10 12:41:04 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

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
	int		start;
	char	quote;

	start = *i;
	while (str[*i] && !ft_strchr(" \t|<>", str[*i]))
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			quote = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else
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

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] && ft_strchr(" \t", input[i]))
			i++;
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			add_token(&tokens, strndup(&input[i], (identify_operator(input, &i) == TOKEN_HEREDOC || identify_operator(input, &i) == TOKEN_APPEND) ? 2 : 1), identify_operator(input, &i));
		else
			add_token(&tokens, identify_word(input, &i), TOKEN_WORD);
	}
	return (tokens);
}

// Main pour test simple
int	main(int argc, char **argv, char **envp)
{
	t_token	*tokens;

	if (argc != 2)
	{
		printf("Usage: %s \"command_line\"\n", argv[0]);
		return (1);
	}
	tokens = tokenize(argv[1]);
	while (tokens)
	{
		printf("Type: %d\tValue: [%s]\n", tokens->type, tokens->value);
		tokens = tokens->next;
	}
	return (0);
}

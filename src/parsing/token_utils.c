/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:03:32 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/28 14:16:01 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_token	*safe_create_token(char *value, t_token_type type, t_quote quote)
{
	t_token *token;

	if (!value)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(value);
		return (NULL);
	}
	token->value = value;
	token->type = type;
	token->quote = quote;
	token->next = NULL;
	return (token);
}

char	**safe_realloc_string_array(char **old_array, size_t new_size)
{
	char **new_array;
	size_t i;
	size_t old_size;

	if (!old_array)
		return (ft_calloc(new_size + 1, sizeof(char *)));

	old_size = 0;
	while (old_array[old_size])
		old_size++;

	new_array = ft_calloc(new_size + 1, sizeof(char *));
	if (!new_array)
		return (old_array);

	i = 0;
	while (i < old_size && i < new_size)
	{
		new_array[i] = old_array[i];
		i++;
	}

	free(old_array);
	return (new_array);
}

int	count_string_array(char **array)
{
	int count;

	if (!array)
		return (0);
	count = 0;
	while (array[count])
		count++;
	return (count);
}
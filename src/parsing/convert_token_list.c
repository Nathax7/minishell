/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:28:44 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/23 18:27:57 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static size_t	count_listed_tokens(t_token *token_list)
{
	size_t	count;
	t_token	*current;

	count = 0;
	current = token_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	free_partial_char_array(char **array, size_t max_i)
{
	size_t	j;

	j = 0;
	while (j < max_i)
	{
		free(array[j]);
		j++;
	}
	free(array);
}

char	**convert_token_list_to_char_array(t_token *token_list)
{
	size_t	token_count;
	char	**char_array;
	t_token	*current;
	size_t	i;

	if (!token_list)
	{
		char_array = (char **)ft_calloc(1, sizeof(char *));
		return (char_array);
	}
	token_count = count_listed_tokens(token_list);
	char_array = (char **)ft_calloc(token_count + 1, sizeof(char *));
	if (!char_array)
		return (NULL);
	current = token_list;
	i = 0;
	while (current)
	{
		if (current->value)
		{
			char_array[i] = ft_strdup(current->value);
			if (!char_array[i])
				return (free_partial_char_array(char_array, i), NULL);
		}
		else                              
			char_array[i] = ft_strdup("");
		i++;
		current = current->next;
	}
	return (char_array);
}

void	free_char_array(char **array)
{
	size_t i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
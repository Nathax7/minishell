/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_token_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:28:44 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/10 22:27:23 by almeekel         ###   ########.fr       */
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

char	**convert_token_list_to_char_array(t_token *token_list)
{
	size_t	token_count;
	char	**char_array;
	t_token	*current;
	size_t	i;
	size_t	j;

	if (!token_list)
	{
		char_array = (char **)malloc(sizeof(char *));
		if (!char_array)
			return (NULL);
		char_array[0] = NULL;
		return (char_array);
	}
	token_count = count_listed_tokens(token_list);
	char_array = (char **)malloc((token_count + 1) * sizeof(char *));
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
			{
				j = 0;
				while (j < i)
					free(char_array[j++]);
				free(char_array);
				return (NULL);
			}
		}
		else
			char_array[i] = NULL; // CA IL NE FAUT PAS QUE CA ARRIVE !!!
		i++;
		current = current->next;
	}
	char_array[i] = NULL;
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
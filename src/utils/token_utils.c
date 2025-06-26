/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:03:32 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/25 18:39:56 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
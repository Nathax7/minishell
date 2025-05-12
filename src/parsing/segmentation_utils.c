/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segmentation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:45:18 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/11 21:45:33 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_word_segment	*create_word_segment(char *value, t_quote quote_type)
{
	t_word_segment	*new_segment;

	new_segment = (t_word_segment *)malloc(sizeof(t_word_segment));
	if (!new_segment)
	{
		free(value);
		return (NULL);
	}
	new_segment->value = value;
	new_segment->quote_type = quote_type;
	new_segment->next = NULL;
	return (new_segment);
}

void	append_segment(t_word_segment **head, t_word_segment *new_segment)
{
	if (!new_segment)
		return ;
	if (*head == NULL)
	{
		*head = new_segment;
	}
	else
	{
		t_word_segment *current = *head;
		while (current->next)
			current = current->next;
		current->next = new_segment;
	}
}
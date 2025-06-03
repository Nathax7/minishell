/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder_annex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:33:14 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/28 16:34:06 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*sb_free_and_return_null(t_str_builder *sb)
{
	if (sb)
	{
		free(sb->str);
		sb->str = NULL;
		sb->len = 0;
		sb->capacity = 0;
	}
	return (NULL);
}

int	sb_free_and_return_zero(t_str_builder *sb)
{
	if (sb)
	{
		free(sb->str);
		sb->str = NULL;
		sb->len = 0;
		sb->capacity = 0;
	}
	return (0);
}

void	sb_free(t_str_builder *sb)
{
	if (sb)
	{
		free(sb->str);
		sb->str = NULL;
		sb->len = 0;
		sb->capacity = 0;
	}
}

char	*sb_to_string_and_free(t_str_builder *sb)
{
	char	*result;

	if (!sb)
		return (ft_strdup(""));
	if (!sb->str)
	{
		sb_free(sb);
		return (ft_strdup(""));
	}
	result = ft_strdup(sb->str);
	sb_free(sb);
	return (result);
}

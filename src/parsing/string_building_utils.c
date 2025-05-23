/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:59:05 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/15 18:43:05 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	sb_init(t_str_builder *sb)
{
	if (!sb)
		return ;
	sb->str = NULL;
	sb->len = 0;
	sb->capacity = 0;
}

int	sb_append_char(t_str_builder *sb, char c)
{
	char	*new_str;
	char	char_to_append[2];

	if (!sb)
		return (0);
	char_to_append[0] = c;
	char_to_append[1] = '\0';
	if (!sb->str)
		new_str = ft_strdup(char_to_append);
	else
	{
		new_str = ft_strjoin(sb->str, char_to_append);
		free(sb->str);
	}
	if (!new_str)
		return (0);
	sb->str = new_str;
	sb->len = ft_strlen(new_str);
	return (1);
}

int	sb_append_str(t_str_builder *sb, const char *s)
{
	char	*new_str;

	if (!sb || !s)
		return (0);
	if (!sb->str)
		new_str = ft_strdup(s);
	else
	{
		new_str = ft_strjoin(sb->str, s);
		free(sb->str);
	}
	if (!new_str)
		return (0);
	sb->str = new_str;
	sb->len = ft_strlen(new_str);
	return (1);
}

char	*sb_to_string(t_str_builder *sb)
{
	char	*result;

	if (!sb || !sb->str)
	{
		result = ft_strdup("");
		if (!result)
			return (NULL);
		return (result);
	}
	result = ft_strdup(sb->str);
	return (result);
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
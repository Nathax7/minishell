/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:59:05 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/28 16:34:20 by almeekel         ###   ########.fr       */
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

static int	sb_ensure_capacity(t_str_builder *sb, size_t needed)
{
	char	*new_str;
	size_t	new_cap;

	if (needed <= sb->capacity)
		return (1);
	new_cap = sb->capacity;
	if (new_cap == 0)
		new_cap = 16;
	while (new_cap < needed)
		new_cap *= 2;
	new_str = ft_calloc(new_cap + 1, sizeof(char));
	if (!new_str)
		return (0);
	if (sb->str)
		ft_strlcpy(new_str, sb->str, sb->len + 1);
	free(sb->str);
	sb->str = new_str;
	sb->capacity = new_cap;
	return (1);
}

int	sb_append_char(t_str_builder *sb, char c)
{
	if (!sb)
		return (0);
	if (!sb_ensure_capacity(sb, sb->len + 1))
		return (0);
	sb->str[sb->len] = c;
	sb->len++;
	sb->str[sb->len] = '\0';
	return (1);
}

int	sb_append_str(t_str_builder *sb, const char *s)
{
	size_t	s_len;
	size_t	i;

	if (!sb || !s)
		return (0);
	s_len = ft_strlen(s);
	if (!sb_ensure_capacity(sb, sb->len + s_len))
		return (0);
	i = 0;
	while (i < s_len)
	{
		sb->str[sb->len + i] = s[i];
		i++;
	}
	sb->len += s_len;
	sb->str[sb->len] = '\0';
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

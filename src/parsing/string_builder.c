/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_builder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:59:05 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/10 23:02:50 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	sb_init(t_str_builder *sb)
{
	if (!sb)
		return ;
	sb->str = NULL;
	sb->len = 0;
	sb->capacity = 0; // Pas forcement utile
}

// Append un charactere au string builder
// Version pas tres efficace avec tous els appels a strjoin
// Une meilleure version serait plus opti
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
		return (0); // alloc echoue
	sb->str = new_str;
	sb->len = ft_strlen(new_str); // met a jour la longueur de la string
	return (1);
}

// Append une chaine de char au builder
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
		return (0); // Allocation fail
	sb->str = new_str;
	sb->len = ft_strlen(new_str);
	return (1);
}

// finalise et re;plit la string
char	*sb_to_string(t_str_builder *sb)
{
	char	*result;

	if (!sb || !sb->str)
	{
		result = ft_strdup(""); // retourne string vide si le builder est vide
		if (!result)
			return (NULL); // fail Malloc
		return (result);
	}
	result = ft_strdup(sb->str); // Dupliaue la string interne
	return (result);
}

// Libere la string interne (sb) du builder
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
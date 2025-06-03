/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:30:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/27 21:32:21 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	is_ifs(char c, const char *ifs)
{
	if (!ifs)
		return (c == ' ' || c == '\t' || c == '\n');
	while (*ifs)
	{
		if (c == *ifs)
			return (1);
		ifs++;
	}
	return (0);
}

static int	count_fields(const char *str, const char *ifs)
{
	int	count;
	int	in_field;

	count = 0;
	in_field = 0;
	while (*str)
	{
		if (is_ifs(*str, ifs))
			in_field = 0;
		else if (!in_field)
		{
			in_field = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*extract_one_field(const char **str_ptr, const char *ifs)
{
	const char	*start;
	char		*field;

	while (**str_ptr && is_ifs(**str_ptr, ifs))
		(*str_ptr)++;
	if (!**str_ptr)
		return (NULL);
	start = *str_ptr;
	while (**str_ptr && !is_ifs(**str_ptr, ifs))
		(*str_ptr)++;
	field = ft_substr(start, 0, *str_ptr - start);
	return (field);
}

static char	**allocate_field_array(const char *str, const char *ifs)
{
	int	field_count;

	field_count = count_fields(str, ifs);
	if (field_count > INT_MAX)
		return (NULL);
	return (ft_calloc(field_count + 1, sizeof(char *)));
}

char	**perform_field_splitting(const char *str, const char *ifs_val)
{
	char		**fields;
	int			idx;
	const char	*current_ptr;
	const char	*current_ifs;

	if (!str)
		return (NULL);
	current_ifs = ifs_val;
	if (!current_ifs)
		current_ifs = " \t\n";
	fields = allocate_field_array(str, current_ifs);
	if (!fields)
		return (NULL);
	idx = 0;
	current_ptr = str;
	while ((fields[idx] = extract_one_field(&current_ptr, current_ifs)))
	{
		if (!fields[idx])
		{
			free_char_array(fields);
			return (NULL);
		}
		idx++;
	}
	fields[idx] = NULL;
	return (fields);
}

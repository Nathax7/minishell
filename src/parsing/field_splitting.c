/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:30:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/11 18:04:37 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	is_sep(char c, const char *sep)
{
	if (!sep)
		return (c == ' ' || c == '\t' || c == '\n');
	while (*sep)
	{
		if (c == *sep)
			return (1);
		sep++;
	}
	return (0);
}

static int	count_fields(const char *str, const char *sep)
{
	int	count;
	int	in_field;

	count = 0;
	in_field = 0;
	while (*str)
	{
		if (is_sep(*str, sep))
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

static char	*extract_one_field(const char **str_ptr, const char *sep)
{
	const char	*start;
	char		*field;

	while (**str_ptr && is_sep(**str_ptr, sep))
		(*str_ptr)++;
	if (!**str_ptr)
		return (NULL);
	start = *str_ptr;
	while (**str_ptr && !is_sep(**str_ptr, sep))
		(*str_ptr)++;
	field = ft_substr(start, 0, *str_ptr - start);
	return (field);
}

static char	**allocate_field_array(const char *str, const char *sep)
{
	int	field_count;

	field_count = count_fields(str, sep);
	return (ft_calloc(field_count + 1, sizeof(char *)));
}

char	**perform_field_splitting(const char *str, const char *sep_val)
{
	char		**fields;
	int			index;
	const char	*current_ptr;
	const char	*current_sep;

	if (!str)
		return (NULL);
	current_sep = sep_val;
	if (!current_sep)
		current_sep = " \t\n";
	fields = allocate_field_array(str, current_sep);
	if (!fields)
		return (NULL);
	index = 0;
	current_ptr = str;
	while ((fields[index] = extract_one_field(&current_ptr, current_sep)))
	{
		if (!fields[index])
			return(ft_freesplit(fields));
		index++;
	}
	fields[index] = NULL;
	return (fields);
}


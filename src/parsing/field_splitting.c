/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:30:28 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/23 18:26:59 by almeekel         ###   ########.fr       */
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

static size_t	count_fields(const char *str, const char *ifs)
{
	size_t	count;
	int		in_field;

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

static char	*extract_one_field(const char **str_ptr, const char *current_ifs)
{
	const char	*start_of_field;
	char		*field;

	while (**str_ptr && is_ifs(**str_ptr, current_ifs))
		(*str_ptr)++;
	if (!**str_ptr)
		return (NULL);
	start_of_field = *str_ptr;
	while (**str_ptr && !is_ifs(**str_ptr, current_ifs))
		(*str_ptr)++;
	field = ft_substr(start_of_field, 0, *str_ptr - start_of_field);
	return (field);
}

char	**perform_field_splitting(const char *str, const char *ifs_val)
{
	char		**fields;
	size_t		num_fields;
	int			idx;
	const char	*current_str_ptr;
	const char	*current_ifs;

	if (!str)
		return (NULL);
	current_ifs = ifs_val ? ifs_val : " \t\n";
	num_fields = count_fields(str, current_ifs);
	fields = (char **)ft_calloc(num_fields + 1, sizeof(char *));
	if (!fields)
		return (NULL);
	idx = 0;
	current_str_ptr = str;
	while (idx < (int)num_fields)
	{
		fields[idx] = extract_one_field(&current_str_ptr, current_ifs);
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

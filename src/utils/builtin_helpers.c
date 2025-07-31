/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:10:01 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/30 18:35:34 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

char	*create_env_string(char *name, char *value)
{
	char	*result;
	int		name_len;
	int		value_len;

	if (!name)
		return (NULL);
	name_len = ft_strlen(name);
	if (!value)
		return (ft_strdup(name));
	value_len = ft_strlen(value);
	result = malloc(name_len + value_len + 2);
	if (!result)
		return (NULL);
	ft_strcpy(result, name);
	result[name_len] = '=';
	ft_strcpy(result + name_len + 1, value);
	return (result);
}

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

int	find_env_index(char **envp, const char *name)
{
	int	i;
	int	name_len;

	if (!envp || !name)
		return (-1);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	print_escaped_value(const char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '"')
			ft_putstr_fd("\\\"", STDOUT_FILENO);
		else if (value[i] == '\\')
			ft_putstr_fd("\\\\", STDOUT_FILENO);
		else
			ft_putchar_fd(value[i], STDOUT_FILENO);
		i++;
	}
}

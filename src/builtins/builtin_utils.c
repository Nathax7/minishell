/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:10:01 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/05 17:02:15 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	is_valid_var_name(const char *name)
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

static char	*create_env_string(const char *name, const char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value ? value : "");
	free(temp);
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
char	*create_env_string(const char *name, const char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

char	*find_env_var(char **envp, const char *name)
{
	int		i;
	size_t	name_len;
	argv
	if (!envp || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (envp[i] + name_len + 1);
		i++;
	}
	return (NULL);
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

char	**copy_env_array(char **envp)
{
	char	**new_env;
	int		count;
	int		i;

	count = count_env_vars(envp);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_env_array(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**resize_env_array(char **envp, int new_size)
{
	char	**new_env;
	int		i;
	int		old_size;

	old_size = count_env_vars(envp);
	new_env = malloc(sizeof(char *) * (new_size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < old_size && i < new_size)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			free_env_array(new_env);
			return (envp);
		}
		i++;
	}
	while (i < new_size)
	{
		new_env[i] = NULL;
		i++;
	}
	return (new_env);
}

void	free_env_array(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_char_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}


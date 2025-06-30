/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shelvl_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:32:13 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/29 19:50:00 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

static char	**copy_basic_env(char **envp)
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
			ft_freesplit(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
static int	add_missing_pwd(char ***env_ptr)
{
	char	*pwd;

	if (find_env_index(*env_ptr, "PWD") != -1)
		return (0);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	if (set_env_var(env_ptr, "PWD", pwd) != 0)
	{
		free(pwd);
		return (-1);
	}
	free(pwd);
	return (0);
}
static int	increment_shlvl(char ***env_ptr)
{
	char	*shlvl_str;
	char	*new_shlvl_str;
	int		shlvl;

	shlvl_str = find_env_value(*env_ptr, "SHLVL");
	shlvl = ft_atoi(shlvl_str ? shlvl_str : "0") + 1;
	new_shlvl_str = ft_itoa(shlvl);
	if (!new_shlvl_str)
		return (-1);
	if (set_env_var(env_ptr, "SHLVL", new_shlvl_str) != 0)
	{
		free(new_shlvl_str);
		return (-1);
	}
	free(new_shlvl_str);
	return (0);
}

static int	add_missing_shlvl(char ***env_ptr)
{
	if (find_env_index(*env_ptr, "SHLVL") == -1)
		return (set_env_var(env_ptr, "SHLVL", "1"));
	else
		return (increment_shlvl(env_ptr));
}

static int	add_missing_underscore(char ***env_ptr)
{
	if (find_env_index(*env_ptr, "_") == -1)
		return (set_env_var(env_ptr, "_", "/usr/bin/env"));
	return (0);
}

char	**copy_env_array(char **envp)
{
	char	**new_env;

	new_env = copy_basic_env(envp);
	if (!new_env)
		return (NULL);
	if (add_missing_pwd(&new_env) == -1)
	{
		if (new_env)
			ft_freesplit(new_env);
		return (NULL);
	}
	if (add_missing_shlvl(&new_env) == -1)
	{
		if (new_env)
			ft_freesplit(new_env);
		return (NULL);
	}
	if (add_missing_underscore(&new_env) == -1)
	{
		if (new_env)
			ft_freesplit(new_env);
		return (NULL);
	}
	return (new_env);
}

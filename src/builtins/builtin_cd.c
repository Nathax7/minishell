/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:40:19 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/19 16:33:23 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	update_pwd_variables(char ***env_ptr, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("cd: getcwd");
		return (1);
	}
	if (old_pwd)
		set_env_var(env_ptr, "OLDPWD", old_pwd);
	set_env_var(env_ptr, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

static char	*find_directory(t_args *args, char **env)
{
	char	*target;

	if (!args->next->cmd_args)
	{
		target = find_env_var(env, "HOME");
		if (!target)
		{
			ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		return (ft_strdup(target));
	}
	else if (ft_strcmp(args->next->cmd_args, "-") == 0)
	{
		target = find_env_var(env, "OLDPWD");
		if (!target)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		ft_putstr_fd(target, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (ft_strdup(target));
	}
	else
		return (ft_strdup(args->next->cmd_args));
}

int	builtin_cd(t_args *args, char ***env_ptr)
{
	char	*target_dir;
	char	*old_pwd;
	int		result;

	if (args->next->cmd_args && args->next->next->cmd_args)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	target_dir = find_directory(args, *env_ptr);
	if (!target_dir)
	{
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	if (chdir(target_dir) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(target_dir);
		free(target_dir);
		if (old_pwd)
			free(old_pwd);
		return (1);
	}
	result = update_pwd_variables(env_ptr, old_pwd);
	free(target_dir);
	if (old_pwd)
		free(old_pwd);
	return (result);
}

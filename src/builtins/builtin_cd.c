/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:40:19 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/29 15:47:49 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
	else
	{
		remove_env_variable(env_ptr, "OLDPWD");
	}
	set_env_var(env_ptr, "PWD", new_pwd);
	free(new_pwd);
	return (0);
}

char	*old_dir(char *target, char **env)
{
	target = find_env_var(env, "OLDPWD");
	if (!target)
	{
		ft_message("cd", NULL, "OLDPWD not set");
		return (NULL);
	}
	ft_putstr_fd(target, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (ft_strdup(target));
}

static char	*find_directory(t_args *args, char **env)
{
	char	*target;
	t_args	*first_arg;

	target = NULL;
	first_arg = args->next;
	if (!first_arg || ft_strcmp(first_arg->cmd_args, "~") == 0
		|| ft_strcmp(first_arg->cmd_args, "~/") == 0)
	{
		target = find_env_var(env, "HOME");
		if (!target)
		{
			ft_message("cd", NULL, "HOME not set");
			return (NULL);
		}
		return (ft_strdup(target));
	}
	else if (first_arg->cmd_args && ft_strlen(first_arg->cmd_args) == 0)
	{
		return (ft_strdup("."));
	}
	else if (ft_strcmp(first_arg->cmd_args, "-") == 0)
		return (old_dir(target, env));
	else
		return (ft_strdup(first_arg->cmd_args));
}

int	error_dir(t_args *args, char **target_dir, char **old_pwd, char ***env_ptr)
{
	*target_dir = find_directory(args, *env_ptr);
	if (!*target_dir)
	{
		if (*old_pwd)
			free(*old_pwd);
		return (1);
	}
	if (chdir(*target_dir) == -1)
	{
		if (errno == ENOENT)
			ft_message("cd", *target_dir, "No such file or directory");
		else if (errno == EACCES)
			ft_message("cd", *target_dir, "Permission denied");
		else if (errno == ENOTDIR)
			ft_message("cd", *target_dir, "Not a directory");
		else
			ft_message("cd", *target_dir, strerror(errno));
		free(*target_dir);
		if (*old_pwd)
			free(*old_pwd);
		return (1);
	}
	return (0);
}

int	builtin_cd(t_args *args, char ***env_ptr)
{
	char	*target_dir;
	char	*old_pwd;
	int		result;
	t_args	*first_arg;
	t_args	*second_arg;

	first_arg = args->next;
	if (first_arg)
		second_arg = first_arg->next;
	else
		second_arg = NULL;
	if (first_arg && second_arg)
		ft_return_message("cd", NULL, "too many arguments", 1);
	old_pwd = find_env_var(*env_ptr, "PWD");
	if (old_pwd)
		old_pwd = ft_strdup(old_pwd);
	else
		old_pwd = NULL;
	if (error_dir(args, &target_dir, &old_pwd, env_ptr) == 1)
		return (1);
	result = update_pwd_variables(env_ptr, old_pwd);
	free(target_dir);
	if (old_pwd)
		free(old_pwd);
	return (result);
}

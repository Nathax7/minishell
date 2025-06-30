/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:40:19 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/29 16:54:53 by almeekel         ###   ########.fr       */
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
	t_args	*first_arg;

	first_arg = args->next;
	
	if (!first_arg)
	{
		target = find_env_var(env, "HOME");
		if (!target)
		{
			ft_message("cd", NULL, "HOME not set");
			return (NULL);
		}
		return (ft_strdup(target));
	}
	else if (ft_strcmp(first_arg->cmd_args, "-") == 0)
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
	else
		return (ft_strdup(first_arg->cmd_args));
}

int	builtin_cd(t_args *args, char ***env_ptr)
{
	char	*target_dir;
	char	*old_pwd;
	int		result;
	t_args	*first_arg;
	t_args	*second_arg;

	first_arg = args->next;
	second_arg = first_arg ? first_arg->next : NULL;
	
	if (first_arg && second_arg)
	{
		ft_message("cd", NULL, "too many arguments");
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
		if (errno == ENOENT)
			ft_message("cd", target_dir, "No such file or directory");
		else if (errno == EACCES)
			ft_message("cd", target_dir, "Permission denied");
		else if (errno == ENOTDIR)
			ft_message("cd", target_dir, "Not a directory");
		else
			ft_message("cd", target_dir, strerror(errno));
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

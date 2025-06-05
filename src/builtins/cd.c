/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:40:19 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/05 16:51:37 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"


static int	cd_home(char **env)
{
	char	*path_home;

	path_home = find_env_var(env, "HOME");
	if (!path_home)
	{
		ft_message("cd", "HOME not set");
		return (1);
	}
	errno = 0;
	if (chdir(path_home))
	{
		ft_message("cd", path_home);
		return (1);
	}
	return (0);
}

static int	cd_old(char **env)
{
	char	*path_old;

	path_old = find_env_var(env, "OLDPWD");
	if (!path_old)
	{
		ft_message("cd", "OLDPWD not set");
		return (1);
	}
	errno = 0;
	ft_putstr_fd(path_old, stderr);
	ft_putstr_fd("\n", stderr);
	if (chdir(path_old))
	{
		ft_message("cd", path_old);
		return (1);
	}
	return (0);
}

int			ft_cd(t_exec *cmd, char **env, int j)
{
	int		err;
	char	*path;

	if (ft_strlen(cmd->group[j]) > 2)
	{
		ft_message("cd", "too many arguments");
		return (1);
	}
	if (cmd->group[j + 1])
	{
		path = cmd->group[j + 1];
		errno = 0;
		if (ft_strcmp("-", path) == 0)
			return (cd_old(*env));
		err = chdir(path);
		if (err)
		{
			ft_message("cd", cmd->group[j + 1]);
			return (1);
		}
		return (0);
	}
	return (cd_home(*env));
}

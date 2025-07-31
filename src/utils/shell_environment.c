/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_environment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:32:13 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/23 15:52:00 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	**copy_env_array(char **envp)
{
	char	**new_env;

	new_env = copy_basic_env(envp);
	if (!new_env)
		return (NULL);
	if (add_missing_pwd(&new_env) == -1)
	{
		ft_freesplit(new_env);
		return (NULL);
	}
	if (add_missing_shlvl(&new_env) == -1)
	{
		ft_freesplit(new_env);
		return (NULL);
	}
	if (add_missing_underscore(&new_env) == -1)
	{
		ft_freesplit(new_env);
		return (NULL);
	}
	return (new_env);
}

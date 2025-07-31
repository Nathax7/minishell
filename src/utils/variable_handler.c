/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:37:24 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/29 17:18:18 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*find_env_value(char **envp, const char *name)
{
	int		index;
	char	*equals_pos;

	index = find_env_index(envp, name);
	if (index == -1)
		return (NULL);
	equals_pos = ft_strchr(envp[index], '=');
	if (!equals_pos)
		return (NULL);
	return (equals_pos + 1);
}

void	remove_env_variable(char ***env_ptr, const char *name)
{
	int	index;
	int	i;

	if (!env_ptr || !*env_ptr || !name)
		return ;
	index = find_env_index(*env_ptr, name);
	if (index == -1)
		return ;
	free((*env_ptr)[index]);
	i = index;
	while ((*env_ptr)[i + 1])
	{
		(*env_ptr)[i] = (*env_ptr)[i + 1];
		i++;
	}
	(*env_ptr)[i] = NULL;
}

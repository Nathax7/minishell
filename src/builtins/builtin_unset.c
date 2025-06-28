/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:55:14 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/28 19:30:45 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	remove_env_var(char ***env_ptr, char *name)
{
	char	**new_env;
	int		index;
	int		count;
	int		i;
	int		j;

	index = find_env_index(*env_ptr, name);
	if (index == -1)
		return (0);
	count = count_env_vars(*env_ptr);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (1);
	i = 0;
	j = 0;
	while (i < count)
	{
		if (i != index)
		{
			new_env[j] = (*env_ptr)[i];
			j++;
		}
		else
			free((*env_ptr)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*env_ptr);
	*env_ptr = new_env;
	return (0);
}

int	builtin_unset(t_args *args, char ***env_ptr)
{
	int exit_status;

	if (!args || !env_ptr)
		return (0);

	args = args->next;
	if (!args || !args->cmd_args)
		return (0);

	exit_status = 0;
	while (args && args->cmd_args)
	{
		if (!is_valid_var_name(args->cmd_args))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args->cmd_args, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else
		{
			if (remove_env_var(env_ptr, args->cmd_args) != 0)
				exit_status = 1;
		}
		args = args->next;
	}
	return (exit_status);
}
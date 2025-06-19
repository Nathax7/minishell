/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:58:56 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/19 16:36:42 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	print_export_format(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
		{
			ft_putchar_fd(envp[i][j], STDOUT_FILENO);
			j++;
		}
		if (envp[i][j] == '=')
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(envp[i] + j + 1, STDOUT_FILENO);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

static int	parse_export_arg(char *arg, char **name, char **value)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (equals)
	{
		*name = ft_substr(arg, 0, equals - arg);
		*value = ft_strdup(equals + 1);
	}
	else
	{
		*name = ft_strdup(arg);
		*value = NULL;
	}
	if (!*name)
		return (0);
	return (is_valid_var_name(*name));
}

int	set_env_var(char ***env_ptr, char *name, char *value)
{
	char	**new_env;
	char	*new_var;
	int		index;
	int		count;

	index = find_env_index(*env_ptr, name);
	new_var = create_env_string(name, value);
	if (!new_var)
		return (1);
	if (index >= 0)
	{
		free((*env_ptr)[index]);
		(*env_ptr)[index] = new_var;
	}
	else
	{
		count = count_env_vars(*env_ptr);
		new_env = malloc(sizeof(char *) * (count + 2));
		if (!new_env)
		{
			free(new_var);
			return (1);
		}
		index = 0;
		while (index < count)
		{
			new_env[index] = (*env_ptr)[index];
			index++;
		}
		new_env[count] = new_var;
		new_env[count + 1] = NULL;
		free(*env_ptr);
		*env_ptr = new_env;
	}
	return (0);
}

int	builtin_export(t_args *args, char ***env_ptr)
{
	char *name;
	char *value;
	int exit_status;

	args = args->next;
	if (!args->cmd_args)
	{
		print_export_format(*env_ptr);
		return (0);
	}
	exit_status = 0;
	while (args->cmd_args)
	{
		if (!parse_export_arg(args->cmd_args, &name, &value))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(args->cmd_args, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		else
		{
			if (set_env_var(env_ptr, name, value) != 0)
				exit_status = 1;
		}
		if (name)
			free(name);
		if (value)
			free(value);
		args = args->next;
	}
	return (exit_status);
}

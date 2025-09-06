/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:58:56 by almeekel          #+#    #+#             */
/*   Updated: 2025/08/18 11:32:32 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	export_with_value(char *name, char *value, char *original_arg,
		char ***env_ptr)
{
	if (name[0] == '-')
	{
		ft_putstr_fd("minishell: export: -", 2);
		ft_putchar_fd(name[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	if (!is_valid_var_name(name))
	{
		ft_message("export", original_arg, "not a valid identifier");
		return (1);
	}
	if (set_env_var(env_ptr, name, value) != 0)
		return (1);
	return (0);
}

static int	export_without_value(char *name, char ***env_ptr)
{
	int	existing_index;

	if (name[0] == '-')
	{
		ft_putstr_fd("minishell: export: -", 2);
		ft_putchar_fd(name[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		return (2);
	}
	if (!is_valid_var_name(name))
	{
		ft_message("export", name, "not a valid identifier");
		return (1);
	}
	existing_index = find_env_index(*env_ptr, name);
	if (existing_index != -1)
		return (0);
	if (set_env_var(env_ptr, name, "") != 0)
		return (1);
	return (0);
}

static int	process_export_arg(char *arg, char ***env_ptr)
{
	char	*equal_pos;
	char	*var_name;
	char	*var_value;
	int		result;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		var_name = ft_substr(arg, 0, equal_pos - arg);
		if (!var_name)
			return (0);
		var_value = equal_pos + 1;
		result = export_with_value(var_name, var_value, arg, env_ptr);
		free(var_name);
		return (result);
	}
	else
		return (export_without_value(arg, env_ptr));
}

static void	print_export_format(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
		{
			ft_putchar_fd(envp[i][j], STDOUT_FILENO);
			j++;
		}
		if (envp[i][j] == '=')
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			print_escaped_value(envp[i] + j + 1);
			ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	builtin_export(t_args *args, char ***env_ptr)
{
	int		exit_status;
	t_args	*current;

	if (!args || !env_ptr || !*env_ptr)
		return (1);
	if (!args->next)
	{
		print_export_format(*env_ptr);
		return (0);
	}
	exit_status = 0;
	current = args->next;
	while (current)
	{
		exit_status = process_export_arg(current->cmd_args, env_ptr);
		current = current->next;
	}
	return (exit_status);
}

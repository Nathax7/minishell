/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:56:30 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/29 18:07:22 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	long_long_checker(const char *str, int i, long long result,
		int sign)
{
	while (str[i] && ft_isdigit(str[i]))
	{
		if (sign == -1 && result == 922337203685477580LL && str[i] == '8')
		{
			result = 9223372036854775808ULL;
			i++;
			break ;
		}
		if (result > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (sign == -1 && (unsigned long long)result > 9223372036854775808ULL)
		return (0);
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	is_numeric_string(const char *str)
{
	int			i;
	long long	result;
	int			sign;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	result = 0;
	return (long_long_checker(str, i, result, sign));
}

void	exit_args(t_exec *exec, int parent, t_args **first_arg)
{
	if (!exec->cmd_list->args)
	{
		ft_putstr_fd("exit\n", 2);
		free_exit(exec, parent, 0);
	}
	(*first_arg) = exec->cmd_list->args->next;
	if (!(*first_arg))
	{
		ft_putstr_fd("exit\n", 2);
		free_exit(exec, parent, 0);
	}
}

void	is_alpha_string(t_exec *exec, t_args *first_arg, int parent)
{
	if (!is_numeric_string(first_arg->cmd_args))
	{
		ft_putstr_fd("exit\n", 2);
		ft_message("exit", first_arg->cmd_args, "numeric argument required");
		free_exit(exec, parent, 2);
	}
}

int	builtin_exit(t_exec *exec, int parent)
{
	int		exit_code;
	t_args	*first_arg;
	t_args	*second_arg;

	exit_args(exec, parent, &first_arg);
	second_arg = first_arg->next;
	if (second_arg)
	{
		if (!is_numeric_string(first_arg->cmd_args))
		{
			ft_putstr_fd("exit\n", 2);
			ft_message("exit", first_arg->cmd_args,
				"numeric argument required");
			free_exit(exec, parent, 255);
		}
		ft_putstr_fd("exit\n", 2);
		ft_message("exit", NULL, "too many arguments");
		return (1);
	}
	is_alpha_string(exec, first_arg, parent);
	exit_code = ft_atoi(first_arg->cmd_args);
	ft_putstr_fd("exit\n", 2);
	free_exit(exec, parent, (unsigned char)exit_code);
	return ((unsigned char)exit_code);
}

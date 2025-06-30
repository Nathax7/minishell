/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:56:30 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/29 18:58:47 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	is_numeric_string(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (!str[i]);
}

int	builtin_exit(t_args *args)
{
	int		exit_code;
	t_args	*first_arg;
	t_args	*second_arg;

	if (!args)
	{
		printf("exit\n");
		exit(0);
	}
	printf("exit\n");
	first_arg = args->next;
	if (!first_arg)
		exit(0);
	second_arg = first_arg->next;
	if (second_arg)
	{
		if (!is_numeric_string(first_arg->cmd_args))
		{
			ft_message("exit", first_arg->cmd_args, "numeric argument required");
			exit(2);
		}
		ft_message("exit", NULL, "too many arguments");
		return (1);
	}
	if (!is_numeric_string(first_arg->cmd_args))
	{
		ft_message("exit", first_arg->cmd_args, "numeric argument required");
		exit(2);
	}
	exit_code = ft_atoi(first_arg->cmd_args);
	exit((unsigned char)exit_code);
}

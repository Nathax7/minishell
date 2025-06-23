/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/23 18:54:35 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/signals.h"

int			g_signal_test = 0;

static int	execute_command_string(char *command, char **env_copy)
{
	t_token	*tokens;
	int		exit_status;
	char	*input_copy;

	input_copy = ft_strdup(command);
	if (!input_copy)
		return (1);
	tokens = parse_complete_input(&input_copy, env_copy, g_signal_test);
	if (!tokens)
	{
		free(input_copy);
		return (1);
	}
	exit_status = pipex(tokens, env_copy);
	g_signal_test = exit_status;
	free_token_list(tokens);
	free(input_copy);
	return (exit_status);
}

static void	interactive_mode(char **env_copy)
{
	char	*input;
	t_token	*tokens;
	int		exit_status;

	while (1)
	{
		input = readline("\033[1;32mminishell$\033[0m ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		tokens = parse_complete_input(&input, env_copy, g_signal_test);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		exit_status = pipex(tokens, env_copy);
		g_signal_test = exit_status;
		free_token_list(tokens);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char **env_copy;
	int exit_status;

	env_copy = copy_env_array(envp);
	if (!env_copy)
		return (EXIT_FAILURE);

	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0)
	{
		exit_status = execute_command_string(argv[2], env_copy);
		ft_freesplit(env_copy);
		return (exit_status);
	}
	else if (argc == 1)
	{
		interactive_mode(env_copy);
		ft_freesplit(env_copy);
		return (g_signal_test);
	}
	else
	{
		ft_putstr_fd("Usage: minishell [-c command]\n", STDERR_FILENO);
		ft_freesplit(env_copy);
		return (EXIT_FAILURE);
	}
}
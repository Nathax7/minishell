/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/04 15:53:25 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "signals.h"

int			g_signal_test = 0;

static int	check_semicolon_syntax(char *command)
{
	int		i;
	int		in_quotes;
	char	quote_char;
	int		last_was_semicolon;

	i = 0;
	in_quotes = 0;
	quote_char = 0;
	last_was_semicolon = 0;
	while (command[i] && ft_isspace(command[i]))
		i++;
	if (command[i] == ';')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `;'\n",
			STDERR_FILENO);
		return (2);
	}
	while (command[i])
	{
		if ((command[i] == '\'' || command[i] == '"') && !in_quotes)
		{
			in_quotes = 1;
			quote_char = command[i];
			last_was_semicolon = 0;
		}
		else if (command[i] == quote_char && in_quotes)
		{
			in_quotes = 0;
			quote_char = 0;
			last_was_semicolon = 0;
		}
		else if (command[i] == ';' && !in_quotes)
		{
			if (last_was_semicolon)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `;'\n",
					STDERR_FILENO);
				return (2);
			}
			last_was_semicolon = 1;
		}
		else if (!ft_isspace(command[i]))
		{
			last_was_semicolon = 0;
		}
		i++;
	}
	return (0);
}

static int	execute_command_string(char *command, char ***env_copy_ptr)
{
	char	**commands;
	int		exit_status;
	int		i;
	int		syntax_error;
	char	*trimmed;
	char	*input_copy;
	t_token	*tokens;

	syntax_error = check_semicolon_syntax(command);
	if (syntax_error != 0)
		return (syntax_error);
	commands = ft_split(command, ';');
	if (!commands)
		return (1);
	exit_status = 0;
	i = 0;
	while (commands[i])
	{
		trimmed = ft_strtrim(commands[i], " \t\n\r\f\v");
		if (trimmed && *trimmed)
		{
			input_copy = ft_strdup(trimmed);
			if (input_copy)
			{
				tokens = parse_complete_input(&input_copy, *env_copy_ptr,
						g_signal_test);
				if (tokens)
				{
					exit_status = pipex(tokens, env_copy_ptr);
					g_signal_test = exit_status;
					free_token_list(tokens);
				}
				else
				{
					exit_status = 2;
					g_signal_test = exit_status;
				}
				free(input_copy);
			}
		}
		if (trimmed)
			free(trimmed);
		i++;
	}
	ft_freesplit(commands);
	return (exit_status);
}

static void	interactive_mode(char ***env_copy_ptr)
{
	char	*input;
	int		exit_status;

	setup_interactive_signals();
	while (1)
	{
		g_signal_test = 0;
		input = readline("\033[1;32mminishell$\033[0m ");
		if (!input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (g_signal_test == 130)
        {
            g_signal_test = 0;
            free(input);
            continue;
        }
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		add_history(input);
		exit_status = execute_command_string(input, env_copy_ptr);
		if (g_signal_test != 130 && g_signal_test != 131)
        	g_signal_test = exit_status;
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
		exit_status = execute_command_string(argv[2], &env_copy);
		ft_freesplit(env_copy);
		return (exit_status);
	}
	else if (argc == 1)
	{
		interactive_mode(&env_copy);
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
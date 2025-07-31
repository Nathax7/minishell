/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:40:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/31 15:29:45 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "signals.h"

int			g_signal_status = 0;

static void	minishell(t_token *tokens, char *line, char ***env_ptr)
{
	int	exit_status;
	// const t_token *head;

	exit_status = g_signal_status;
	if (g_signal_status)
	{
		if (g_signal_status == 130)
			exit_status = 130;
		g_signal_status = 0;
	}
	if (line)
		tokens = parse_complete_input(line, *env_ptr, &exit_status);
	if (tokens)
	{
		exit_status = exec(tokens, env_ptr);
		g_signal_status = exit_status;
	}
	else
		g_signal_status = exit_status;
}

void	ft_readline(t_token *tokens, char ***env_ptr)
{
	char	*line;

	while (1)
	{
		rl_done = 0;
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
		if (*line == '\0' && g_signal_status != 130)
		{
			free(line);
			continue ;
		}
		if (isatty(fileno(stdin)))
			add_history(line);
		minishell(tokens, line, env_ptr);
		if (line)
			free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	**env_copy;
	t_token	*tokens;

	(void)av;
	tokens = NULL;
	env_copy = copy_env_array(envp);
	if (!env_copy)
		return (EXIT_FAILURE);
	if (ac == 1)
	{
		setup_interactive_signals();
		ft_readline(tokens, &env_copy);
		ft_freesplit(env_copy);
		return (g_signal_status);
	}
	else
	{
		ft_putstr_fd("Usage: minishell [-c command]\n", STDERR_FILENO);
		ft_freesplit(env_copy);
		return (EXIT_FAILURE);
	}
}

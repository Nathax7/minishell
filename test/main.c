/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/25 18:40:14 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "signals.h"

int	g_signal_test = 0;

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_token *tokens;
	char **env_copy;
	int exit_status;

	(void)argc;
	(void)argv;
	env_copy = copy_env_array(envp);
	if (!env_copy)
		return (EXIT_FAILURE);
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
	// Final cleanup
	ft_freesplit(env_copy);
	return (g_signal_test);
}
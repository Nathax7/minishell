/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:13:51 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/09 17:26:46 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	shell_loop(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input) {
			printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);

		// Tokenize
		tokens = tokenize(input);
		print_tokens(tokens);

		// Envoi vers parsing -> execution (à faire)
		// t_command *cmd = parse_tokens(tokens);
		// exec_command(cmd);

		free_tokens(tokens);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	shell_loop();
	return (0);
}

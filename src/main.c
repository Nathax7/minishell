/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:05:36 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 14:08:33 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	g_signal = 0;

static void	free_cmd_list(t_cmd *c) { /* … */ }

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)ac; (void)av;
	while ((line = readline("minishell$> ")))
	{
		add_history(line);
		/* 1 / Tokenisation */
		tokens = tokenizer(line);
		process_quotes(tokens);
		expand_variables(tokens, envp, 0);
		/* 2 /  construire l'AST */
		cmds = build_cmd_list(tokens);
		/* 3 / Heredocs */
		if (!fill_heredocs(cmds))
			execute(cmds, envp);    /* Nathan c'est la que tu interviens           */
		free_cmd_list(cmds);
		free_tokens(tokens);
		free(line);
	}
	printf("exit\n");
	return (0);
}

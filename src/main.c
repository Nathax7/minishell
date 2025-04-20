/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 14:05:36 by almeekel          #+#    #+#             */
/*   Updated: 2025/04/20 16:08:39 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	g_signal;

int	main(int ac, char **av, char **envp)
{
	(void)ac; (void)av;
	char	*line;
	t_cmd	*cmds;

	while ((line = readline("minishell$> ")))
	{
		add_history(line);
		cmds = ft_parsing(line, envp, 0);
		if (!cmds)
		{
			free(line);
			continue ;
		}
		if (!fill_heredocs(cmds))
			execute(cmds, envp);
		free_cmd_list(cmds);
		free(line);
	}
	printf("exit\n");
	return (0);
}


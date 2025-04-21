/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:39:38 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/21 22:29:25 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parsing.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	t_cmd *cmds = parse_line(av[1]);
	t_cmd *tmp = cmds;
	t_cmd *tmp2 = cmds;
	while (tmp)
	{
		printf("Node:\n");
		printf("  Type: %d\n", tmp->type);
		if (tmp->file)
			printf("  File: %s\n", tmp->file);
		if (tmp->cmd_args)
		{
			printf("  Args:");
			for (int i = 0; tmp->cmd_args[i]; i++)
				printf(" %s", tmp->cmd_args[i]);
			printf("\n");
		}
		if (tmp->limiter)
			printf("  Limiter: %s\n", tmp->limiter);
		tmp = tmp->next;
	}
	exec(tmp2, 2, envp);
}
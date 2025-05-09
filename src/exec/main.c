/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:05:00 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/09 17:04:36 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	free_split(char **str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_triple(char ***triple)
{
	char	***p;

	p = triple;
	while (p && *p)
	{
		free_split(*p);
		p++;
	}
	free(triple);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	int		j;
	t_exec	exec;

	(void)ac;
	// (void)av;
	// char *input[] = {
	// 	"cmd1", "|", "cmd2", "|", "cmd3",
	// 	"<", "infile4", "<", "infile5",
	// 	NULL
	// };
	split_pipeline_groups(&exec, av + 1);
	if (!exec.groups)
	{
		free_exec(&exec, -1, NULL, NULL);
		printf("Erreur : résultat NULL\n");
		return (1);
	}
	i = 0;
	while (exec.groups[i])
	{
		printf("Groupe %d : ", i);
		j = 0;
		while (exec.groups[i][j])
		{
			printf("\"%s\" ", exec.groups[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	i = 0;
	j = 0;
	while (exec.groups[i])
	{
		while (exec.groups[i][j])
			j++;
		pipex(&exec, j, exec.groups[i], envp);
		i++;
		j = 0;
	}
	free_pipex(&exec, -1, NULL, NULL);
	return (0);
}


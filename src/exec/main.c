/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:05:00 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/23 22:49:35 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int main(int ac, char **av, char **envp)
{
	int i;
	int j;

	(void)ac;
	// (void)av;
	// char *input[] = {
	// 	"cmd1", "|", "cmd2", "|", "cmd3",
	// 	"<", "infile4", "<", "infile5",
	// 	NULL
	// };

	char ***result = split_pipeline_groups(av + 1);
	if (!result)
	{
		printf("Erreur : résultat NULL\n");
		return 1;
	}
	i = 0;
	while (result[i])
	{
		printf("Groupe %d : ", i);
		j = 0;
		while (result[i][j])
		{
			printf("\"%s\" ", result[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	i = 0;
	j = 0;
	while (result[i])
	{
		while (result[i][j])
			j++;
		pipex(j, result[i], envp);
		i++;
		j = 0;
	}
	free_triple(result);
	return 0;
}

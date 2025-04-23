/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:05:00 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/23 18:55:27 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int main(void)
{
	char *input[] = {
		"cmd1", "|", "cmd2", "|", "cmd3",
		"<", "infile4", "<", "infile5",
		NULL
	};

	char ***result = split_pipeline_groups(input);
	if (!result)
	{
		printf("Erreur : résultat NULL\n");
		return 1;
	}

	int i = 0;
	while (result[i])
	{
		printf("Groupe %d : ", i);
		int j = 0;
		while (result[i][j])
		{
			printf("\"%s\" ", result[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	// Libération de la mémoire
	free_triple(result);
	return 0;
}

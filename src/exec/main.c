/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:05:00 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/07 19:09:59 by nagaudey         ###   ########.fr       */
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

int main(int ac, char **av, char **envp)
{
	int i;
	int j;
	t_exec exec;

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
		return 1;
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
		pipex(j, exec.groups[i], envp);
		i++;
		j = 0;
	}
    i = 0;
    if (exec.groups)
    {
        while (exec.groups[i])
        {
            j = 0;
            while (exec.groups[i][j])
            {
                free(exec.groups[i][j]);
                j++;
            }
            free(exec.groups[i]);
            i++;
        }
        free(exec.groups);
    }
    if (exec.infile)
	{
        free(exec.infile_name);
	}
	if (exec.cmds)
	{
		free(exec.cmds);
	}
    if (exec.outfile)
	{
        free(exec.outfile_name);
	}
	return 0;
}

//si y'a que 2 arguments, infile et outfile, faire une fonction qui copie l'un dans l'autre

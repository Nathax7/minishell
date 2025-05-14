/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:47:28 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/14 15:54:29 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/exec.h"

int g_exit_status = 0;

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
	char **parse;
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
		printf("infile: \"%s\"\n", exec.infile_name[i]);
		printf("outfile: \"%s\"\n", exec.outfile_name[i]);
		i++;
	}
	exec.i = 0;
	exec.j = 0;
	while (exec.groups[exec.i])
	{
		while (exec.groups[exec.i][exec.j])
		exec.j++;
		pipex(&exec, exec.j, exec.groups[exec.i], envp);
		exec.i++;
		exec.j = 0;
	}
	//free_pipex(&exec, -1, NULL, NULL);
	return (0);
}
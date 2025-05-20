/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:47:28 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/20 21:18:27 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"

int		g_exit_status = 0;

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
	t_exec *head;
	t_exec *cur;
	int i, j;

	(void)ac;
	head = split_pipeline_groups(av + 1);
	if (!head)
	{
		fprintf(stderr, "Erreur : résultat NULL\n");
		return (1);
	}
	cur = head;
	i = 0;
	while (cur)
	{
		printf("Groupe %d : ", i);
		j = 0;
		while (cur->group && cur->group[j])
		{
			printf("\"%s\" ", cur->group[j]);
			j++;
		}
		printf("\n");
		printf("  infile: \"%s\"\n",
			cur->infile_name ? cur->infile_name : "(none)");
		printf("  outfile: \"%s\"\n",
			cur->outfile_name ? cur->outfile_name : "(none)");
		cur = cur->next;
		i++;
	}
	cur = head;
	while (cur)
	{
		j = 0;
		while (cur->group && cur->group[j])
			j++;
		pipex(cur, j, cur->group, envp);
		cur = cur->next;
	}
	free_exec(head, -1, NULL, NULL);
	return (0);
}
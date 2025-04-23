/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:01:32 by nagaudey          #+#    #+#             */
/*   Updated: 2025/04/23 18:29:20 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	free_split(char **arr)
{
	for (char **p = arr; p && *p; ++p)
		free(*p);
	free(arr);
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

static int	is_token(const char *tok, const char *s)
{
	return (ft_strcmp(tok, s) == 0);
}

static char	**allocate_cmd_buffer(int count)
{
	return (malloc((count + 1) * sizeof(char *)));
}

static char	***allocate_groups(int count)
{
	return (malloc((count + 1) * sizeof(char **)));
}

static char	**finalize_group(char **cmds, int ncmd, char *infile, char *outfile)
{
	int		total;
	char	**group;
	int		idx;
	int		j;

	total = ncmd;
	if (infile)
		total = total + 1;
	if (outfile)
		total = total + 1;
	group = malloc((total + 1) * sizeof(char *));
	if (!group)
		return (NULL);
	idx = 0;
	if (infile)
	{
		group[idx] = infile;
		idx = idx + 1;
	}
	j = 0;
	while (j < ncmd)
	{
		group[idx] = cmds[j];
		idx = idx + 1;
		j = j + 1;
	}
	if (outfile)
	{
		group[idx] = outfile;
		idx = idx + 1;
	}
	group[idx] = NULL;
	if (idx == 0)
	{
		group[0] = ft_strdup("0");
		group[1] = NULL;
	}
	return (group);
}

char	***split_pipeline_groups(char **tokens)
{
	int		count;
	char	***groups;
	char	**cmds;
	int		i;
	int		ncmd;
	int		ng;
	char	*infile;
	char	*outfile;
	char	**group;


	count = 0;
	while (tokens && tokens[count])
		count = count + 1;
	groups = allocate_groups(count);
	if (!groups)
		return (NULL);
	cmds = allocate_cmd_buffer(count);
	if (!cmds)
	{
		free(groups);
		return (NULL);
	}
	i = 0;
	ncmd = 0;
	ng = 0;
	infile = NULL;
	outfile = NULL;
	while (i < count)
	{
		if (is_token(tokens[i], "<") && i + 1 < count)
		{
			free(infile);
			infile = ft_strdup(tokens[i + 1]);
			i = i + 2;
		}
		else if (is_token(tokens[i], ">") && i + 1 < count)
		{
			free(outfile);
			outfile = ft_strdup(tokens[i + 1]);
			i = i + 2;
			if (!(i < count && is_token(tokens[i], ">")))
			{
				group = finalize_group(cmds, ncmd, infile, outfile);
				if (!group)
					break ;
				groups[ng] = group;
				ng = ng + 1;
				ncmd = 0;
				infile = NULL;
				outfile = NULL;
			}
		}
		else if (is_token(tokens[i], "|"))
		{
			i = i + 1;
		}
		else
		{
			cmds[ncmd] = ft_strdup(tokens[i]);
			ncmd = ncmd + 1;
			i = i + 1;
		}
	}
	if (ncmd > 0 || infile || outfile)
	{
		group = finalize_group(cmds, ncmd, infile, outfile);
		if (group)
		{
			groups[ng] = group;
			ng = ng + 1;
		}
	}
	groups[ng] = NULL;
	free(cmds);
	return (groups);
}

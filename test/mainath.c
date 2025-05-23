/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:47:28 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/23 16:05:13 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/parsing.h"

int				g_exit_status = 0;

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

static t_token	*add_token(t_token **head, t_token **tail, t_token_type type,
		const char *value)
{
	t_token	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = strdup(value);
	node->next = NULL;
	if (*tail)
		(*tail)->next = node;
	else
		*head = node;
	*tail = node;
	return (node);
}

static void	print_exec_list(t_exec *cur)
{
	int	i;
	int j;

	i = 0;
	j = 0;
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
}

int	main(int ac, char **av, char **envp)
{
	t_exec	*head;
	t_exec	*cur;
	t_token *tokens;
	t_token *tail;
	int j;

	(void)ac;
	(void)av;
	tokens = NULL;
	tail = NULL;
	add_token(&tokens, &tail, T_REDIRECT_IN, "<");
	add_token(&tokens, &tail, T_WORD, "infile2");
	add_token(&tokens, &tail, T_REDIRECT_IN, "<");
	add_token(&tokens, &tail, T_WORD, "Makefe");
	add_token(&tokens, &tail, T_WORD, "cat");
	add_token(&tokens, &tail, T_REDIRECT_OUT, ">");
	add_token(&tokens, &tail, T_WORD, "cat");
	add_token(&tokens, &tail, T_REDIRECT_IN, "<");
	add_token(&tokens, &tail, T_WORD, "infile2");
	add_token(&tokens, &tail, T_REDIRECT_IN, "<");
	add_token(&tokens, &tail, T_WORD, "Makefile");
	add_token(&tokens, &tail, T_WORD, "cat");
	head = split_pipeline_groups(tokens);
	free_token(tokens, -1, NULL, NULL);
	if (!head)
	{
		fprintf(stderr, "Error: failed to split pipeline\n");
		return (EXIT_FAILURE);
	}
	cur = head;
	print_exec_list(cur);
	cur = head;
	while (cur)
	{
		j = 0;
		while (cur->group && cur->group[j])
			j++;
		if (cur->group)
			pipex(cur, j, cur->group, envp);
		cur = cur->next;
	}
	free_exec(head, -1, NULL, NULL);
	return (0);
}

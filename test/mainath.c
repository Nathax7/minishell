/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:47:28 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/28 16:55:56 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

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
		printf("  infile: \"%s\"",
			cur->infile_name ? cur->infile_name : "(none)");
		printf("  (heredoc = %d)", cur->heredoc);
		printf("\n");
		printf("  outfile: \"%s\"",
			cur->outfile_name ? cur->outfile_name : "(none)");
		printf("  (append = %d)", cur->append);
		printf("\n");
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
	int status;

	(void)ac;
	(void)av;
	tokens = NULL;
	tail = NULL;

	add_token(&tokens, &tail, T_REDIRECT_IN, "<");
	add_token(&tokens, &tail, T_WORD, "Makefile");
    add_token(&tokens, &tail, T_WORD, "cat");
    add_token(&tokens, &tail, T_PIPE, "|");
    add_token(&tokens, &tail, T_WORD, "cat");
	add_token(&tokens, &tail, T_REDIRECT_OUT, ">");
    add_token(&tokens, &tail, T_WORD, "out2");
	add_token(&tokens, &tail, T_REDIRECT_IN, "<");
	add_token(&tokens, &tail, T_WORD, "Makefile");
    add_token(&tokens, &tail, T_WORD, "cat");
	add_token(&tokens, &tail, T_REDIRECT_OUT, ">");
    add_token(&tokens, &tail, T_WORD, "out");

	// // quand y'a | > bash skip tout ce qu'il y avait avant (mais pas toujours)

	head = split_pipeline_groups(tokens);
	free_token(tokens, -1, NULL, NULL);
	if (!head->group)
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
		status = pipex(cur, j, cur->group, envp);
		// verifier si les cmds sont not found dans chaque groupe et ne pas lancer le grp si c'est le cas
		// if (status == 127)
		// 	break;
		cur = cur->next;
	}
	free_exec(head, -1, NULL, NULL);
	return (status);
}

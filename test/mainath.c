/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:47:28 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/23 18:50:14 by almeekel         ###   ########.fr       */
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

static void	print_exec_list(t_pipex_input *cur)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (cur)
	{
		printf("Groupe %d : ", i);
		j = 0;
		while (cur->cmd_argv && cur->cmd_argv[j])
		{
			printf("\"%s\" ", cur->cmd_argv[j]);
			j++;
		}
		printf("\n");
		printf("  infile: \"%s\"\n",
			cur->config_node->infile_name ? cur->config_node->infile_name : "(none)");
		printf("  outfile: \"%s\"\n",
			cur->config_node->outfile_name ? cur->config_node->outfile_name : "(none)");
		cur->config_node = cur->config_node->next;
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex_input	head;
	t_pipex_input	cur;
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
	head = prepare_pipeline_for_pipex(tokens);
	free_token(tokens, -1, NULL, NULL);
	if (head.config_node)
	{
		fprintf(stderr, "Error: failed to split pipeline\n");
		return (EXIT_FAILURE);
	}
	cur = head;
	print_exec_list(&cur);
	cur = head;
	while (cur.config_node)
	{
		j = 0;
		while (cur.config_node->group && cur.config_node->group[j])
			j++;
		if (cur.config_node->group)
			pipex(cur.config_node, cur.cmd_argc, cur.cmd_argv, envp);
		cur.config_node = cur.config_node->next;
	}
	free_exec(head.config_node, -1, NULL, NULL);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:49:01 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/10 23:01:33 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int g_exit_status = 0;
volatile sig_atomic_t	g_signal_received = 0;

// pour afficer le type d etoken
static void	print_token_type_core(t_token_type type)
{
	if (type == T_WORD)
		printf("T_WORD");
	else if (type == T_PIPE)
		printf("T_PIPE");
	else if (type == T_REDIRECT_IN)
		printf("T_REDIRECT_IN");
	else if (type == T_REDIRECT_OUT)
		printf("T_REDIRECT_OUT");
	else if (type == T_APPEND)
		printf("T_APPEND");
	else if (type == T_HEREDOC)
		printf("T_HEREDOC");
	else
		printf("T_UNKNOWN");
}
// pour afficher le status des quote
static void	print_quote_status_core(t_quote quote)
{
	if (quote == Q_NONE)
		printf("Q_NONE");
	else if (quote == Q_SINGLE)
		printf("Q_SINGLE");
	else if (quote == Q_DOUBLE)
		printf("Q_DOUBLE");
	else
		printf("Q_UNKNOWN_QUOTE_STATUS");
}
// pour afficher les token
static void	display_tokens_core(t_token *token_list)
{
	t_token	*current;
	int		i;

	i = 0;
	current = token_list;
	if (!current)
	{
		printf("No tokens generated (or lexer error occurred).\n");
		return ;
	}
	printf("Tokens (from lexer):\n");
	while (current)
	{
		printf("  [%d]: Value=\"%s\", Type=", i++, current->value);
		print_token_type_core(current->type);
		printf(", Quote=");
		print_quote_status_core(current->quote);
		printf("\n");
		current = current->next;
	}
}
// pour afficher les chaines de caracteres
static void	display_char_array_core(char **array)
{
	int	i;

	i = 0;
	if (!array || !array[0])
	{
		printf("Char array is empty or NULL.\n");
		return ;
	}
	printf("Tokens (as char** array):\n");
	while (array[i])
	{
		printf("  [%d]: \"%s\"\n", i, array[i]);
		i++;
	}
}

int	main(void)
{
	char *line;
	t_token *token_list;
	char **char_array_tokens;

	printf("Core Parser Test (string_builder, lexer, lexer_utils, convert_token_list, error)\n");
	printf("Ctrl+D or 'exit' to quit.\n");

	while (1)
	{
		g_exit_status = 0;
		line = readline("test_core_parser> ");
		if (line == NULL || ft_strcmp(line, "exit") == 0)
		{
			if (line)
				free(line);
			printf("Exiting core parser test.\n");
			break ;
		}
		if (*line)
			add_history(line);
		printf("\nInput: \"%s\"\n", line);
		token_list = lexer(line);
		display_tokens_core(token_list);

		if (token_list)
		{
			char_array_tokens = convert_token_list_to_char_array(token_list);
			display_char_array_core(char_array_tokens);
			free_char_array(char_array_tokens);
		}

		free_token_list(token_list);
		free(line);
		printf("g_exit_status after processing: %d\n", g_exit_status);
		printf("--------------NATHAX----------------\n");
	}
	rl_clear_history();
	return (g_exit_status);
}
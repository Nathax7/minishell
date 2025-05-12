/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:49:01 by almeekel          #+#    #+#             */
/*   Updated: 2025/05/11 21:47:16 by almeekel         ###   ########.fr       */
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
static void	display_tokens_core(t_token *token_list, bool is_raw_list)
{
    t_token	*current_token;
    int		i;

    i = 0;
    current_token = token_list;
    if (!current_token)
    {
        printf("No tokens generated (or error occurred).\n");
        return ;
    }
    // printf("Tokens:\n"); // Generic title
    while (current_token)
    {
        printf("  [%d]: Type=", i++);
        print_token_type_core(current_token->type);

        if (current_token->type == T_WORD)
        {
            if (is_raw_list && current_token->segments)
            {
                printf("\n    Segments:\n");
                t_word_segment *seg = current_token->segments;
                int j = 0;
                while(seg)
                {
                    printf("      Seg[%d]: Value=\"%s\", Quote=", j++, seg->value);
                    print_quote_status_core(seg->quote_type);
                    printf("\n");
                    seg = seg->next;
                }
            }
            else // Expanded T_WORD or if segments somehow not present
            {
                printf(", Value=\"%s\", Quote=", current_token->value ? current_token->value : "(null)");
                print_quote_status_core(current_token->quote); // Should be Q_NONE after expansion
                printf("\n");
            }
        }
        else // Operators
        {
            printf(", Value=\"%s\", Quote=", current_token->value);
            print_quote_status_core(current_token->quote); // Should be Q_NONE
            printf("\n");
        }
        current_token = current_token->next;
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

int	main(int ac, char **av, char **envp)
{
    char	*line;
    t_token	*raw_token_list;
    t_token	*expanded_token_list;
    char	**char_array_tokens;

    (void)ac;
    (void)av;
    printf("Core Parser Test (lexer, expander, converter, error handling)\n");
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

        // 1. Lexing
        raw_token_list = lexer(line);
        printf("\n--- Tokens (raw, from lexer): ---\n");
        display_tokens_core(raw_token_list, true); // Pass true for raw list

        // 2. Expansion
        if (raw_token_list && g_exit_status == 0) // Proceed only if lexing was successful
        {
            expanded_token_list = perform_all_expansions(raw_token_list, envp, g_exit_status);
            printf("\n--- Tokens (after expansion): ---\n");
            display_tokens_core(expanded_token_list, false); // Pass false for expanded list

            // 3. Conversion of expanded tokens to char**
            if (expanded_token_list && g_exit_status == 0) // Proceed only if expansion was successful
            {
                char_array_tokens = convert_token_list_to_char_array(expanded_token_list);
                printf("\n--- Tokens (expanded, as char** array): ---\n");
                display_char_array_core(char_array_tokens);
                free_char_array(char_array_tokens);
            }
            free_token_list(expanded_token_list); // Free the list from expansion
        }

        free_token_list(raw_token_list); // Free the original list from lexer
        free(line);
        printf("\ng_exit_status after processing: %d\n", g_exit_status);
        printf("--------------MINISHELL_TEST_CYCLE_END----------------\n");
    }
    rl_clear_history();
    return (g_exit_status);
}
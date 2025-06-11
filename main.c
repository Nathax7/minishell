/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/11 17:46:54 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/builtins.h"
#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/signals.h"

int			g_signal_test = 0;

// void	print_shell_status(void)
// {
// 	if (g_signal_test != 0)
// 		printf("\033[0;31m[Exit: %d]\033[0m ", g_signal_test);
// }

// AJOUTER EXIT 130 CHECK ICI ?
// static int	process_input_line(char *input, char **env_copy)
// {
// 	t_token	*tokens;
// 	t_exec	*exec_tree;

// 	if (!*input)
// 		return (0);
// 	add_history(input);
// 	tokens = parse_complete_input(&input, env_copy, g_signal_test);
// 	if (!tokens)
// 		return (0);
// 	split_pipeline_groups(tokens);
// 	// if (exec_tree)
// 	// {
// 	// 	setup_child_signals();
// 	// 	// g_signal_test = exec_pipeline(exec_tree, env_copy);
// 	// 	setup_interactive_signals();
// 	// 	free_exec_core(exec_tree);
// 	// }
// 	free_token_list(tokens);
// 	return (1);
// }
// static void	print_exec_list(t_exec *cur)
// {
// 	int	i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (cur)
// 	{
// 		printf("Groupe %d : ", i);
// 		j = 0;
// 		while (cur->group && cur->group[j])
// 		{
// 			printf("\"%s\" ", cur->group[j]);
// 			j++;
// 		}
// 		printf("\n");
// 		printf("  infile: \"%s\"",
// 			cur->infile_name ? cur->infile_name : "(none)");
// 		printf("  (heredoc = %d)", cur->heredoc);
// 		printf("\n");
// 		printf("  outfile: \"%s\"",
// 			cur->outfile_name ? cur->outfile_name : "(none)");
// 		printf("  (append = %d)", cur->append);
// 		printf("\n");
// 		cur = cur->next;
// 		i++;
// 	}
// }

int	main_shell_loop(char **envp)
{
    char	*input;
    int		status;
    t_exec	*head;
    t_exec	*cur;
    t_token	*tokens;
    char	**env_copy;

    env_copy = copy_env_array(envp);
    if (!env_copy)
        return (EXIT_FAILURE);
    
    while (1)
    {
        input = readline("\033[1;32mminishell$\033[0m ");
        
        // Handle Ctrl+D (EOF) or readline error
        if (!input)
        {
            printf("exit\n");
            break;
        }
        
        // Skip empty input
        if (*input == '\0')
        {
            free(input);
            continue;
        }
        
        add_history(input);
        tokens = parse_complete_input(&input, env_copy, g_signal_test);
        if (!tokens)
        {
            free(input);
            continue;
        }
        
        head = split_pipeline_groups(tokens);
        free_token_list(tokens);  // Fix: use free_token_list instead of free_token
        
        if (!head)
        {
            free(input);
            continue;
        }
        
        // print_exec_list(head);
        
        // Execute each pipeline group
        cur = head;
        while (cur)
        {
            if (cur->group && cur->group[0])
            {
                int j = 0;
                while (cur->group[j])
                    j++;
                status = pipex(cur, j, cur->group, env_copy);
                g_signal_test = status;

                // Debug: Check if stdin is still valid
                // if (isatty(STDIN_FILENO) == 0)
                // {
                //     fprintf(stderr, "ERROR: stdin is no longer a terminal after pipex!\n");
                //     // Try to restore stdin
                //     int new_stdin = open("/dev/tty", O_RDONLY);
                //     if (new_stdin != -1)
                //     {
                //         dup2(new_stdin, STDIN_FILENO);
                //         close(new_stdin);
                //     }
                // }
            }
            cur = cur->next;
        }
        
        free_exec_core(head);  // Fix: use free_exec_core instead of free_exec
        free(input);
    }
    
    ft_freesplit(env_copy);
    return (g_signal_test);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	return (main_shell_loop(envp));
}
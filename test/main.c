/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/19 18:12:18 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/builtins.h"

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
// }// 	i = 0;
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

// int	main_shell_loop(char **envp, t_token *tokens)
// {
// 	char	*input;
	
// 	while (1)
// 	{
// 		input = readline("\033[1;32mminishell$\033[0m ");
// 		// Handle Ctrl+D (EOF) or readline error
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		// Skip empty input
// 		if (*input == '\0')
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		add_history(input);
// 		if (!tokens)
// 		{
// 			free(input);
// 			continue ;
// 		}
// 		pipex(tokens, envp);
// 		free_token_list(tokens);
// 	}
// 	ft_freesplit(env_copy);
// 	return (g_signal_test);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char *input;
// 	t_token *tokens;
// 	char **env_copy;

// 	env_copy = copy_env_array(envp);
// 	if (!env_copy)
// 		return (EXIT_FAILURE);
// 	if (!tokens)
// 	{
// 		ft_freesplit(env_copy);
// 		return (EXIT_FAILURE);
// 	}
// 	if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 'c')
// 	{
// 		input = argv[2];
// 		env_copy = copy_env_array(envp);
// 		if (!env_copy)
// 			return (EXIT_FAILURE);
// 		pipex(tokens, envp);
// 	}
// 	free_token_list(tokens);
// 	return (main_shell_loop(envp));
// }

#include "../includes/exec.h"
#include "../includes/parsing.h"
#include "../includes/signals.h"

int	g_signal_test = 0;

int	main_shell_loop(char **envp)
{
    char	*input;
    t_token	*tokens;
    int		exit_status;
    
    while (1)
    {
        input = readline("\033[1;32mminishell$\033[0m ");
        if (!input)
        {
            printf("exit\n");
            break ;
        }
        if (*input == '\0')
        {
            free(input);
            continue ;
        }
        add_history(input);
        tokens = parse_complete_input(&input, envp, g_signal_test);
        if (!tokens)
        {
            free(input);
            continue ;
        }
        exit_status = pipex(tokens, envp);
        g_signal_test = exit_status;
        
        free(input);
    }
    return (g_signal_test);
}

int	main(int argc, char **argv, char **envp)
{
    char	*input;
    t_token	*tokens;
    char	**env_copy;
    int		exit_status;

    if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 'c')
    {
        input = ft_strdup(argv[2]);
        if (!input)
            return (EXIT_FAILURE);
        
        env_copy = copy_env_array(envp);
        if (!env_copy)
        {
            free(input);
            return (EXIT_FAILURE);
        }
        tokens = parse_complete_input(&input, env_copy, g_signal_test);
        if (!tokens)
        {
            free(input);
            ft_freesplit(env_copy);
            return (EXIT_FAILURE);
        }
        // Execute the tokens
        exit_status = pipex(tokens, env_copy);
        // Cleanup
        free(input);
        ft_freesplit(env_copy);
        return (exit_status);
    }
    // Interactive shell mode
    env_copy = copy_env_array(envp);
    if (!env_copy)
        return (EXIT_FAILURE);
    
    exit_status = main_shell_loop(env_copy);
    ft_freesplit(env_copy);
    return (exit_status);
}
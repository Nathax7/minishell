/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/03 11:16:36 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/exec.h"
#include <signal.h>

int g_exit_status = 0;
volatile sig_atomic_t g_signal_received = 0;

static void	handle_sigint(int sig)
{
    (void)sig;
    g_signal_received = 1;
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void	setup_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}

static void	print_welcome(void)
{
    ft_putstr_fd("\n", STDOUT_FILENO);
    ft_putstr_fd("╔══════════════════════════════════════╗\n", STDOUT_FILENO);
    ft_putstr_fd("║            MINISHELL v1.0            ║\n", STDOUT_FILENO);
    ft_putstr_fd("║     A simple bash-like shell        ║\n", STDOUT_FILENO);
    ft_putstr_fd("╚══════════════════════════════════════╝\n", STDOUT_FILENO);
    ft_putstr_fd("\n", STDOUT_FILENO);
}

static char	**convert_tokens_to_command_array(t_token *tokens)
{
    char	**cmd_array;
    t_token	*current;
    int		count;
    int		i;

    if (!tokens)
        return (NULL);
    
    count = 0;
    current = tokens;
    while (current)
    {
        if (current->type == T_WORD)
            count++;
        current = current->next;
    }
    
    cmd_array = malloc(sizeof(char *) * (count + 1));
    if (!cmd_array)
        return (NULL);
    
    i = 0;
    current = tokens;
    while (current && i < count)
    {
        if (current->type == T_WORD)
        {
            cmd_array[i] = ft_strdup(current->value);
            if (!cmd_array[i])
            {
                while (--i >= 0)
                    free(cmd_array[i]);
                free(cmd_array);
                return (NULL);
            }
            i++;
        }
        current = current->next;
    }
    cmd_array[i] = NULL;
    return (cmd_array);
}

static int	execute_pipeline(t_token *tokens, char **envp)
{
    t_exec		exec;
    char		**cmd_array;
    int			cmd_count;
    int			status;

    if (!tokens)
        return (0);

    cmd_array = convert_tokens_to_command_array(tokens);
    if (!cmd_array)
        return (1);

    cmd_count = 0;
    while (cmd_array[cmd_count])
        cmd_count++;

    if (cmd_count == 0)
    {
        free_char_array(cmd_array);
        return (0);
    }

    status = pipex(&exec, cmd_count, cmd_array, envp);
    
    free_char_array(cmd_array);
    return (status);
}

static int	is_builtin_command(const char *cmd)
{
    if (!cmd)
        return (0);
    
    if (ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0);
}

static int	execute_builtin(t_token *tokens, char ***envp)
{
    char	*cmd;
    
    if (!tokens || tokens->type != T_WORD)
        return (0);
    
    cmd = tokens->value;
    
    if (ft_strcmp(cmd, "exit") == 0)
    {
        ft_putstr_fd("exit\n", STDOUT_FILENO);
        exit(g_exit_status);
    }
    else if (ft_strcmp(cmd, "pwd") == 0)
    {
        char *cwd = getcwd(NULL, 0);
        if (cwd)
        {
            ft_putendl_fd(cwd, STDOUT_FILENO);
            free(cwd);
            return (0);
        }
        return (1);
    }
    else if (ft_strcmp(cmd, "env") == 0)
    {
        int i = 0;
        while ((*envp)[i])
        {
            ft_putendl_fd((*envp)[i], STDOUT_FILENO);
            i++;
        }
        return (0);
    }
    
    // Other builtins would be implemented here
    return (0);
}

static int	process_command_line(t_token *tokens, char ***envp)
{
    if (!tokens)
        return (0);

    // Check if it's a builtin command
    if (tokens->type == T_WORD && is_builtin_command(tokens->value))
        return (execute_builtin(tokens, envp));
    
    // Execute as external command/pipeline
    return (execute_pipeline(tokens, *envp));
}

static void	minishell_loop(char **envp)
{
    char	*line;
    t_token	*tokens;
    char	**env_copy;
    int		i;

    // Create a copy of envp that we can modify
    i = 0;
    while (envp[i])
        i++;
    env_copy = malloc(sizeof(char *) * (i + 1));
    if (!env_copy)
        return;
    i = 0;
    while (envp[i])
    {
        env_copy[i] = ft_strdup(envp[i]);
        i++;
    }
    env_copy[i] = NULL;

    while (1)
    {
        if (g_signal_received)
        {
            g_signal_received = 0;
            g_exit_status = 130;
        }

        line = secure_readline("minishell$ ");
        if (!line)
        {
            ft_putstr_fd("exit\n", STDOUT_FILENO);
            break;
        }

        if (*line == '\0')
        {
            free(line);
            continue;
        }

        tokens = parse_complete_input(&line, env_copy, g_exit_status);
        if (tokens)
        {
            g_exit_status = process_command_line(tokens, &env_copy);
            free_token_list(tokens);
        }
        
        if (line)
            free(line);
    }

    // Free env_copy
    i = 0;
    while (env_copy[i])
    {
        free(env_copy[i]);
        i++;
    }
    free(env_copy);
}

int	main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    if (!envp)
    {
        ft_putstr_fd("minishell: no environment\n", STDERR_FILENO);
        return (1);
    }

    setup_signals();
    print_welcome();
    minishell_loop(envp);

    return (g_exit_status);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:00 by almeekel          #+#    #+#             */
/*   Updated: 2025/06/19 15:49:11 by nagaudey         ###   ########.fr       */
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
void	print_files_detailed(t_files *files)
{
    t_files	*current;
    int		file_index;

    if (!files)
    {
        printf("    📁 FILES: None\n");
        return;
    }

    current = files;
    file_index = 0;
    printf("    📁 FILES:\n");

    while (current)
    {
        printf("    ┌─ File [%d] ──────────────────────────────────────────┐\n", file_index);
        printf("    │ 📍 Address: %p                                     │\n", (void *)current);

        if (current->infile_name)
            printf("    │ 📥 Input: %-37s│\n", current->infile_name);
        else
            printf("    │ 📥 Input: (none)                                  │\n");

        if (current->outfile_name)
            printf("    │ 📤 Output: %-36s│\n", current->outfile_name);
        else
            printf("    │ 📤 Output: (none)                                 │\n");

        printf("    │ 📜 Heredoc: %-34s│\n", current->heredoc ? "✅ YES" : "❌ NO");
        printf("    │ ➕ Append: %-35s│\n", current->append ? "✅ YES" : "❌ NO");
        printf("    └──────────────────────────────────────────────────────┘\n");

        current = current->next;
        file_index++;
    }
    printf("    📊 Total files: %d\n", file_index);
}

void	print_args_detailed(t_args *args)
{
    t_args	*current;
    int		arg_index;

    if (!args)
    {
        printf("    📝 ARGUMENTS: None\n");
        return;
    }

    current = args;
    arg_index = 0;
    printf("    📝 ARGUMENTS:\n");

    while (current)
    {
        printf("    ┌─ Arg [%d] ────────────────────────────────────────────┐\n", arg_index);
        printf("    │ 📍 Address: %p                                    │\n", (void *)current);

        if (current->cmd_args)
            printf("    │ 📝 Value: \"%-35s\" │\n", current->cmd_args);
        else
            printf("    │ 📝 Value: (NULL)                                  │\n");

        printf("    └───────────────────────────────────────────────────────┘\n");

        current = current->next;
        arg_index++;
    }
    printf("    📊 Total arguments: %d\n", arg_index);
}

void	print_single_cmd_detailed(t_cmd *cmd, int cmd_index)
{
    if (!cmd)
    {
        printf("🚫 Command [%d]: NULL\n", cmd_index);
        return;
    }

    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                      COMMAND [%d] DETAILS                       ║\n", cmd_index);
    printf("╠════════════════════════════════════════════════════════════════╣\n");
    printf("║ 📍 Memory: %p                                            ║\n", (void *)cmd);
    printf("╚════════════════════════════════════════════════════════════════╝\n");

    /* Basic info */
    printf("📂 Command path: %s\n", cmd->cmd_path ? cmd->cmd_path : "(not set)");

    /* Flags */
    printf("🔧 Builtin: %s\n", cmd->is_builtin ? "✅ YES" : "❌ NO");

    /* Arguments */
    printf("\n");
    print_args_detailed(cmd->args);

    /* Files */
    printf("\n");
    print_files_detailed(cmd->files);

    /* Navigation */
    printf("\n🔗 NAVIGATION:\n");
    printf("    ⬅️  Previous: %p\n", (void *)cmd->prev);
    printf("    ➡️  Next: %p\n", (void *)cmd->next);
}

void	print_cmd_list_detailed(t_cmd *cmd_list)
{
    t_cmd	*current;
    int		cmd_count;
    int		total_commands;

    if (!cmd_list)
    {
        printf("🚫 Command list is empty (NULL)\n");
        return;
    }

    /* Count total commands */
    current = cmd_list;
    total_commands = 0;
    while (current)
    {
        total_commands++;
        current = current->next;
    }

    /* Header */
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    COMMAND LIST ANALYSIS                    ║\n");
    printf("║                   Total commands: %-3d                      ║\n", total_commands);
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");

    /* Print each command */
    current = cmd_list;
    cmd_count = 0;
    while (current)
    {
        print_single_cmd_detailed(current, cmd_count);

        if (current->next)
        {
            printf("\n🔄 PIPELINE: Command [%d] ──→ Command [%d]\n", cmd_count, cmd_count + 1);
            printf("═══════════════════════════════════════════════════════════════\n");
        }

        current = current->next;
        cmd_count++;
    }

    printf("\n╚═══════════════════ END OF ANALYSIS ═══════════════════════╝\n");
}

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
        free_token_list(tokens);  // Fix: use free_token_list instead of free_token
        if (!head)
        {
            free(input);
            continue;
        }
        pipex(tokens, envp);
        // print_exec_list(head);

        // Execute each pipeline group
        cur = head;

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
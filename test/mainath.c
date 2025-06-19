/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:06:23 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/19 16:06:35 by nagaudey         ###   ########.fr       */
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
void	free_token_list(t_token *tokens)
{
    t_token	*current;
    t_token	*next;

    current = tokens;
    while (current)
    {
        next = current->next;
        if (current->value)
            free(current->value);
        free(current);
        current = next;
    }
}

int	main(int ac, char **av, char **envp)
{
	t_token *tokens;
	t_token *tail;
    int status;

	(void)ac;
	(void)av;
	tokens = NULL;
	tail = NULL;

    add_token(&tokens, &tail, T_WORD, "cat");
    add_token(&tokens, &tail, T_REDIRECT_IN, "<");
    add_token(&tokens, &tail, T_WORD, "Makefile");
    add_token(&tokens, &tail, T_PIPE, "|");
    add_token(&tokens, &tail, T_WORD, "cat");
    add_token(&tokens, &tail, T_REDIRECT_OUT, ">");
    add_token(&tokens, &tail, T_WORD, "out2");


	// // quand y'a | > bash skip tout ce qu'il y avait avant (mais pas toujours

	//free_token(tokens, -1, NULL, NULL);
    status = pipex(tokens, envp);
    free_token_list(tokens);
	return (status);
}
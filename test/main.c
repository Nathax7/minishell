#include "../includes/minishell.h" 

int						g_exit_status = 0;
volatile sig_atomic_t	g_signal_received = 0;

// --- Fonctions utilitaires pour le main ---

static char	**copy_envp(char **envp_main)
{
    int		count;
    char	**new_envp;
    int		i;

    count = 0;
    while (envp_main && envp_main[count])
        count++;
    new_envp = (char **)malloc(sizeof(char *) * (count + 1));
    if (!new_envp)
        return (NULL);
    i = 0;
    while (i < count)
    {
        new_envp[i] = ft_strdup(envp_main[i]);
        if (!new_envp[i])
        {
            while (--i >= 0)
                free(new_envp[i]);
            free(new_envp);
            return (NULL);
        }
        i++;
    }
    new_envp[count] = NULL;
    return (new_envp);
}

// Fonction pour joindre un tableau de chaînes en une seule chaîne avec un séparateur
// Vous pourriez avoir besoin de l'ajouter à votre libft ou utils.
static char	*join_string_array(char **arr, const char *sep)
{
    t_str_builder	sb;
    int				i;

    if (!arr || !arr[0])
        return (ft_strdup(""));
    sb_init(&sb);
    i = 0;
    while (arr[i])
    {
        if (!sb_append_str(&sb, arr[i]))
        {
            sb_free(&sb);
            return (NULL);
        }
        if (arr[i + 1])
        {
            if (!sb_append_str(&sb, (char *)sep)) // sb_append_str prend const char*
            {
                sb_free(&sb);
                return (NULL);
            }
        }
        i++;
    }
    return (sb_to_string(&sb)); // sb_to_string s'occupe de sb_free
}

// Fonction pour préparer et exécuter le pipeline en utilisant la logique existante
// C'est ici que le "pont" est fait.
static int	prepare_and_run_pipeline(t_exec *exec_list_head, char **envp_copy)
{
    t_exec	pipeline_state_holder;
    char	**commands_as_strings;
    int		num_cmds;
    t_exec	*current_node;
    t_exec	*last_node;
    int		i;
    int		status;

    if (!exec_list_head)
        return (g_exit_status);
    num_cmds = 0;
    current_node = exec_list_head;
    last_node = exec_list_head;
    while (current_node)
    {
        num_cmds++;
        if (!current_node->next)
            last_node = current_node;
        current_node = current_node->next;
    }
    if (num_cmds == 0)
        return (0);

    commands_as_strings = (char **)malloc(sizeof(char *) * (num_cmds + 1));
    if (!commands_as_strings)
    {
        perror("minishell: malloc error for commands_as_strings");
        return (1);
    }
    current_node = exec_list_head;
    i = 0;
    while (i < num_cmds)
    {
        commands_as_strings[i] = join_string_array(current_node->group, " ");
        if (!commands_as_strings[i])
        {
            perror("minishell: malloc error joining command group");
            while (--i >= 0)
                free(commands_as_strings[i]);
            free(commands_as_strings);
            return (1);
        }
        current_node = current_node->next;
        i++;
    }
    commands_as_strings[num_cmds] = NULL;

    // Initialiser pipeline_state_holder.
    // pipex_init s'occupe de la sous-structure pipex.
    // Les redirections globales sont prises du premier/dernier noeud.
    ft_memset(&pipeline_state_holder, 0, sizeof(t_exec)); // Important
    pipeline_state_holder.infile_name = exec_list_head->infile_name; // Peut être NULL
    pipeline_state_holder.heredoc = exec_list_head->heredoc;
    pipeline_state_holder.outfile_name = last_node->outfile_name; // Peut être NULL
    pipeline_state_holder.append = last_node->append;
    // Note: Les fd infile/outfile de pipeline_state_holder ne sont pas ouverts ici,
    // pipex_bonus.c -> ft_parse (qui est mal nommé) s'en charge.

    // Appel de votre fonction pipex existante.
    // Elle attend une seule structure t_exec pour l'état global,
    // le nombre de commandes, et un char** où chaque élément est une chaîne de commande.
    status = pipex(&pipeline_state_holder, num_cmds, commands_as_strings, envp_copy);
    // free_pipex est appelée à l'intérieur de pipex en cas d'erreur ou à la fin.
    // Cependant, pipeline_state_holder est sur la stack, donc free_exec_core dessus est un problème.
    // free_pipex devrait être revu pour ne pas free la structure t_exec elle-même si elle est sur la stack.
    // Pour l'instant, on espère que free_pipex libère seulement les membres alloués dynamiquement de pipeline_state_holder.pipex.

    i = 0;
    while (commands_as_strings[i])
    {
        free(commands_as_strings[i]);
        i++;
    }
    free(commands_as_strings);

    return (status); // pipex devrait retourner le statut du dernier cmd
}


int	main(int argc, char **argv, char **envp_main)
{
    char	*line_read;
    t_token	*raw_tokens;
    t_token	*expanded_tokens;
    t_exec	*exec_list_head;
    char	**envp_copy;

    (void)argc;
    (void)argv;
    // Pas de gestion de signaux pour l'instant, comme demandé.
    // initialize_signals();

    envp_copy = copy_envp(envp_main);
    if (!envp_copy && envp_main && envp_main[0]) // S'assurer que envp_main n'est pas juste {NULL}
    {
        perror("minishell: failed to copy environment");
        return (1);
    }

    while (1)
    {
        line_read = secure_readline("minishell> "); // de readline_secure.c
        if (line_read == NULL) // EOF (Ctrl+D)
        {
            ft_putstr_fd("exit\n", STDOUT_FILENO);
            break;
        }
        if (*line_read == '\0') // Ligne vide
        {
            free(line_read);
            continue;
        }
        // add_history est géré par secure_readline

        // 1. Lexing
        raw_tokens = lexer(line_read);
        if (!raw_tokens) // Erreur du lexer (ex: quote non fermée)
        {
            // g_exit_status devrait être mis à jour par le lexer/report_syntax_error
            free(line_read);
            continue;
        }

        // 2. Expansion
        expanded_tokens = perform_all_expansions(raw_tokens, envp_copy, g_exit_status);
        free_token_list(raw_tokens); // Plus besoin des tokens bruts
        if (!expanded_tokens) // Erreur de l'expander
        {
            // g_exit_status devrait être mis à jour par l'expander
            free(line_read);
            continue;
        }

        // 3. Parsing en structure de commandes (liste de t_exec)
        exec_list_head = split_pipeline_groups(expanded_tokens);
        free_token_list(expanded_tokens); // Plus besoin des tokens expansés
        if (!exec_list_head) // Erreur du parser
        {
            // g_exit_status devrait être mis à jour (ex: via report_syntax_error)
            // S'assurer que c'est 2 pour les erreurs de syntaxe.
            if (g_exit_status == 0 && *line_read) g_exit_status = 2;
            free(line_read);
            continue;
        }

        // 4. Exécution
        // Note: `prepare_and_run_pipeline` tente de s'adapter à votre `pipex` existant.
        // La structure `pipeline_state_holder` passée à `pipex` est sur la stack.
        // Votre `free_pipex` doit être conscient de cela et ne pas essayer de `free`
        // la structure `t_exec` elle-même, seulement ses membres alloués.
        g_exit_status = prepare_and_run_pipeline(exec_list_head, envp_copy);


        // 5. Nettoyage de l'itération
        free_exec_list(exec_list_head); // Libère la liste de t_exec et leurs contenus
        free(line_read);
        line_read = NULL;
    }

    // Nettoyage final
    if (envp_copy)
        free_char_array(envp_copy); // Supposant que free_char_array libère chaque chaîne puis le tableau
    // rl_clear_history(); // Optionnel

    return (g_exit_status);
}
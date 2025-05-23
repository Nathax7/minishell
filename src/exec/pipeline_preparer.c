#include "../../includes/parsing.h" // For t_token, t_exec, sb_*, etc.
#include "../../includes/struct.h"  // For t_exec definition

static t_exec	*create_new_exec_node(t_exec *previous_node)
{
	t_exec	*node;

	node = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!node)
		return (NULL); // Erreur d'allocation
	node->prev = previous_node;
	// Les champs infile, outfile (FDs) et la sous-structure pipex
	// sont initialisés à zéro/NULL par ft_calloc.
	return (node);
}

// Ajoute un nœud à la fin de la liste chaînée t_exec.
static void	append_exec_node(t_exec **list_head, t_exec **current_tail,
		t_exec *new_node)
{
	if (!*list_head)
	{
		*list_head = new_node;
		*current_tail = new_node;
	}
	else
	{
		(*current_tail)->next = new_node;
		new_node->prev = *current_tail;
		*current_tail = new_node;
	}
}

// --- Gestion des Arguments pour un Nœud t_exec ---

// Ajoute un argument (chaîne) à une liste temporaire (t_list).
static int	add_argument_to_temp_list(t_list **temp_args, const char *arg_value)
{
	char	*value_copy;
	t_list	*new_link;

	value_copy = ft_strdup(arg_value);
	if (!value_copy)
		return (0); // Erreur d'allocation
	new_link = ft_lstnew(value_copy);
	if (!new_link)
	{
		free(value_copy);
		return (0); // Erreur d'allocation
	}
	ft_lstadd_back(temp_args, new_link);
	return (1);
}

// Convertit la liste temporaire d'arguments en char** et l'assigne à node->group.
static int	finalize_node_arguments(t_exec *node, t_list **temp_args_ptr)
{
	int		arg_count;
	t_list	*current_link;
	int		i;

	if (!node || !temp_args_ptr)
		return (0); // Arguments invalides
	arg_count = ft_lstsize(*temp_args_ptr);
	node->group = (char **)ft_calloc(arg_count + 1, sizeof(char *));
	if (!node->group)
	{
		ft_lstclear(temp_args_ptr, free);
			// Nettoie la liste temporaire en cas d'erreur
		return (0);                       // Erreur d'allocation
	}
	current_link = *temp_args_ptr;
	i = 0;
	while (current_link)
	{
		node->group[i++] = (char *)current_link->content;
		current_link->content = NULL; // Transfère la possession du char*
		current_link = current_link->next;
	}
	ft_lstclear(temp_args_ptr, free);
		// Libère les nœuds t_list (pas le contenu transféré)
	*temp_args_ptr = NULL;
	return (1);
}

// --- Gestion des Redirections pour un Nœud t_exec ---

// Définit un nom de fichier de redirection (infile ou outfile).
static int	assign_redirection_filename(char **filename_field,
		const char *source_value)
{
	char	*value_copy;

	value_copy = ft_strdup(source_value);
	if (!value_copy)
		return (0);        // Erreur d'allocation
	free(*filename_field); // Libère l'ancien nom de fichier s'il existe
	*filename_field = value_copy;
	return (1);
}

// Traite un token de redirection et son nom de fichier associé.
// Avance *current_token_node_ptr au-delà du nom de fichier.
// Retourne: 1 (succès), 0 (erreur malloc), -1 (erreur de syntaxe).
static int	handle_node_redirection(t_exec *exec_node,
		t_token **current_token_node_ptr)
{
	t_token	*operator_token;
	t_token	*filename_token;
	int		is_successful;

	operator_token = *current_token_node_ptr;
	filename_token = operator_token->next;
	is_successful = 1;
	if (!filename_token || filename_token->type != T_WORD)
	{
		// report_syntax_error_detail("nom manquant pour la redirection", NULL);
			// Votre fonction d'erreur
		return (-1); // Erreur de syntaxe
	}
	if (operator_token->type == T_REDIRECT_IN)
		is_successful = assign_redirection_filename(&exec_node->infile_name,
				filename_token->value);
	else if (operator_token->type == T_HEREDOC)
	{
		is_successful = assign_redirection_filename(&exec_node->infile_name,
				filename_token->value);
		if (is_successful)
			exec_node->heredoc = 1;
	}
	else if (operator_token->type == T_REDIRECT_OUT)
		is_successful = assign_redirection_filename(&exec_node->outfile_name,
				filename_token->value);
	else if (operator_token->type == T_APPEND)
	{
		is_successful = assign_redirection_filename(&exec_node->outfile_name,
				filename_token->value);
		if (is_successful)
			exec_node->append = 1;
	}
	*current_token_node_ptr = filename_token; // Avance le pointeur de token
	return (is_successful ? 1 : 0);
}

// --- Logique Principale de Construction de la Liste ---

// Structure d'aide locale pour gérer l'état de la construction.
typedef struct s_exec_list_builder_state
{
	t_token		*current_token;
	t_exec		*list_head;
	t_exec		*current_exec_node;
	t_list *temp_arg_list;
		// Arguments pour la commande en cours de construction
	int build_status;      // 1:ok, 0:erreur malloc, -1:erreur syntaxe
}				t_exec_list_builder_state;

// Initialise l'état du constructeur.
static void	initialize_builder_state(t_exec_list_builder_state *state,
		t_token *tokens)
{
	state->current_token = tokens;
	state->list_head = NULL;
	state->current_exec_node = NULL;
	state->temp_arg_list = NULL;
	state->build_status = 1; // OK par défaut
	if (tokens)              // S'il y a des tokens, créez le premier nœud t_exec
	{
		state->current_exec_node = create_new_exec_node(NULL);
		if (!state->current_exec_node)
			state->build_status = 0; // Erreur Malloc
		else
			append_exec_node(&state->list_head, &state->current_exec_node,
				state->current_exec_node);
	}
}

// Gère un token T_PIPE : finalise la commande actuelle crée un nouveau nœud t_exec.
static void	process_pipe_token(t_exec_list_builder_state *state)
{
	t_exec	*new_node;

	if (!state->current_exec_node)
		// Ne devrait pas arriver si des tokens existent et valides
	{
		state->build_status = (state->build_status == 1 ?
				-1 : state->build_status);
		return ;
	}
	if (!finalize_node_arguments(state->current_exec_node,
			&state->temp_arg_list))
	{
		state->build_status = 0; // Erreur Malloc
		return ;
	}
	new_node = create_new_exec_node(state->current_exec_node);
		// Le nœud actuel devient prev
	if (!new_node)
	{
		state->build_status = 0; // Erreur Malloc
		return ;
	}
	append_exec_node(&state->list_head, &state->current_exec_node, new_node);
}

// Traite le token courant pour construire la liste t_exec.
static void	process_token_for_list(t_exec_list_builder_state *state)
{
	t_token_type	type;

	// Si la création du premier nœud a échoué mais il reste des tokens
	if (!state->current_exec_node && state->current_token)
	{
		state->build_status = 0; // Erreur Malloc antérieure
		return ;
	}
	type = state->current_token->type;
	if (type == T_WORD)
	{
		if (!add_argument_to_temp_list(&state->temp_arg_list,
				state->current_token->value))
			state->build_status = 0;
	}
	else if (type >= T_REDIRECT_IN && type <= T_HEREDOC) // Redirections
	{
		state->build_status = handle_node_redirection(state->current_exec_node,
														&state->current_token);
															// current_token est avancé à l'intérieur
	}
	else if (type == T_PIPE)
		process_pipe_token(state);
	// D'autres types de tokens (ex: opérateurs logiques) nécessiteraient une gestion ici.
}

// Fonction principale pour construire la liste chaînée de t_exec à partir des tokens.
// Renvoie la tête de la liste, ou NULL en cas d'erreur.
t_exec	*parse_tokens_to_exec_list(t_token *expanded_tokens)
{
	t_exec_list_builder_state state;

	initialize_builder_state(&state, expanded_tokens);
	if (state.build_status == 0 && expanded_tokens)    
		// Erreur malloc sur le premier nœud
		return (free_exec_list(state.list_head), NULL);
			// free_exec_list est à implémenter
	if (!expanded_tokens)
		return (NULL); // Pas de tokens, pas de liste
	while (state.current_token && state.build_status > 0)
	{
		process_token_for_list(&state);
		// Avance le token si ce n'est pas déjà fait par un handler (comme handle_node_redirection)
		if (state.current_token && state.build_status > 0)
		{
			state.current_token = state.current_token->next;
		}
	}
	// Finalise les arguments pour la dernière commande de la liste
	if (state.build_status > 0 && state.current_exec_node)
	{
		if (!finalize_node_arguments(state.current_exec_node,
				&state.temp_arg_list))
			state.build_status = 0;
	}
	if (state.build_status <= 0) // En cas d'erreur malloc ou syntaxique
	{
		ft_lstclear(&state.temp_arg_list, free);
			// Nettoie les args temporaires non finalisés
		return (free_exec_list(state.list_head), NULL);
	}
	return (state.list_head);
}
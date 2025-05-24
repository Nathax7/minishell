#include "../../includes/parsing.h"
#include "../../includes/struct.h" // For t_exec

// --- t_exec Node Management ---

static t_exec	*create_new_exec_node(void)
{
    t_exec	*node;

    node = (t_exec *)ft_calloc(1, sizeof(t_exec));
    if (!node)
        report_error_and_exit("malloc error creating exec node"); // Or return NULL
    // node->group, infile_name, outfile_name are NULL due to ft_calloc
    // node->append, heredoc are 0 due to ft_calloc
    // node->next is NULL due to ft_calloc
    return (node);
}

static void	add_exec_node_to_list(t_exec **head, t_exec **current,
                                    t_exec *new_node)
{
    if (!*head)
    {
        *head = new_node;
        *current = new_node;
    }
    else
    {
        (*current)->next = new_node;
        *current = new_node;
    }
}

// --- Argument Group Management for a t_exec Node ---

// Adds a single argument string (value) to a temporary t_list.
static int	add_arg_to_temp_list(t_list **arg_list, const char *value)
{
    char	*arg_copy;
    t_list	*new_link;

    arg_copy = ft_strdup(value);
    if (!arg_copy)
        return (0); // Malloc error
    new_link = ft_lstnew(arg_copy);
    if (!new_link)
    {
        free(arg_copy);
        return (0); // Malloc error
    }
    ft_lstadd_back(arg_list, new_link);
    return (1);
}

// Converts the temporary t_list of args to node->group (char **).
static int	finalize_node_group_from_list(t_exec *node, t_list **arg_list)
{
    int		count;
    t_list	*current_link;
    int		i;

    count = ft_lstsize(*arg_list);
    node->group = (char **)ft_calloc(count + 1, sizeof(char *));
    if (!node->group)
    {
        ft_lstclear(arg_list, free); // Clear list if group allocation fails
        return (0);
    }
    current_link = *arg_list;
    i = 0;
    while (current_link)
    {
        node->group[i] = (char *)current_link->content; // Transfer ownership
        current_link->content = NULL; // Avoid double free by ft_lstclear
        current_link = current_link->next;
        i++;
    }
    // node->group[count] is already NULL from ft_calloc
    ft_lstclear(arg_list, free); // Free list structure (content was moved)
    *arg_list = NULL;            // Reset caller's list pointer
    return (1);
}

// --- Redirection Handling for a t_exec Node ---

// Sets infile details for the current t_exec node.
static int	set_node_infile(t_exec *node, const char *filename, int is_heredoc)
{
    char	*name_copy;

    name_copy = ft_strdup(filename);
    if (!name_copy)
        return (0); // Malloc error
    free(node->infile_name); // Free previous, if any
    node->infile_name = name_copy;
    node->heredoc = is_heredoc;
    return (1);
}

// Sets outfile details for the current t_exec node.
static int	set_node_outfile(t_exec *node, const char *filename, int is_append)
{
    char	*name_copy;

    name_copy = ft_strdup(filename);
    if (!name_copy)
        return (0); // Malloc error
    free(node->outfile_name); // Free previous, if any
    node->outfile_name = name_copy;
    node->append = is_append;
    return (1);
}

// Processes a redirection token and its associated filename.
// Advances *current_token_ptr past the filename.
// Returns 1 (success), 0 (malloc error), -1 (syntax error).
static int	handle_node_redirection(t_exec *node, t_token **current_token_ptr)
{
    t_token	*op_token;
    t_token	*filename_token;
    int		status;

    op_token = *current_token_ptr;
    filename_token = op_token->next;
    if (!filename_token || filename_token->type != T_WORD)
    {
        report_syntax_error(filename_token ? filename_token->value : "newline");
        return (-1); // Syntax error
    }
    status = 1;
    if (op_token->type == T_REDIRECT_IN)
        status = set_node_infile(node, filename_token->value, 0);
    else if (op_token->type == T_HEREDOC)
        status = set_node_infile(node, filename_token->value, 1);
    else if (op_token->type == T_REDIRECT_OUT)
        status = set_node_outfile(node, filename_token->value, 0);
    else if (op_token->type == T_APPEND)
        status = set_node_outfile(node, filename_token->value, 1);
    *current_token_ptr = filename_token; // Consume filename token
    return (status);                     // 1 for success, 0 for malloc error
}

// --- Main Pipeline Building Logic ---

// Helper structure for managing state during pipeline list construction
typedef struct s_pipeline_build_state {
    t_token *current_token;
    t_exec	*pipeline_head;
    t_exec	*current_exec_node;
    t_list	*current_args_list; // Temporary list for char* args
    int		status; // 1=ok, 0=malloc error, -1=syntax error
}			t_pipeline_build_state;

static void	initialize_build_state(t_pipeline_build_state *state,
                                    t_token *tokens)
{
    state->current_token = tokens;
    state->pipeline_head = NULL;
    state->current_exec_node = NULL;
    state->current_args_list = NULL;
    state->status = 1;
    if (tokens) // Create first node only if there are tokens
    {
        state->current_exec_node = create_new_exec_node();
        if (!state->current_exec_node)
            state->status = 0; // Malloc error for first node
        else
            add_exec_node_to_list(&(state->pipeline_head),
                &(state->current_exec_node), state->current_exec_node);
    }
}

static void	handle_pipe_token(t_pipeline_build_state *state)
{
    t_exec	*new_node;

    if (!finalize_node_group_from_list(state->current_exec_node,
            &(state->current_args_list)))
    {
        state->status = 0; // Malloc error in finalizing group
        return;
    }
    new_node = create_new_exec_node();
    if (!new_node)
    {
        state->status = 0; // Malloc error for new node
        return;
    }
    add_exec_node_to_list(&(state->pipeline_head),
        &(state->current_exec_node), new_node);
    // current_args_list is already NULLed by finalize_node_group_from_list
}

// Processes one token and updates the build state.
static void	process_one_token_for_pipeline(t_pipeline_build_state *state)
{
    if (state->current_token->type == T_WORD)
    {
        if (!add_arg_to_temp_list(&(state->current_args_list),
                state->current_token->value))
            state->status = 0;
    }
    else if (state->current_token->type >= T_REDIRECT_IN
        && state->current_token->type <= T_HEREDOC)
    {
        state->status = handle_node_redirection(state->current_exec_node,
                &(state->current_token)); // Advances current_token
        // status from handle_node_redirection is 1, 0, or -1
    }
    else if (state->current_token->type == T_PIPE)
    {
        handle_pipe_token(state);
    }
    // current_token will be advanced in the main loop if not by a handler
}

// Main function to build the t_exec linked list.
// Returns head of the list, or NULL on error (malloc or syntax).
// On error, any partially built list is freed.
t_exec	*build_exec_pipeline_list(t_token *expanded_tokens)
{
    t_pipeline_build_state	state;

    if (!expanded_tokens)
        return (NULL);
    initialize_build_state(&state, expanded_tokens);
    if (state.status == 0) // Malloc error during init
        return (free_exec_list(state.pipeline_head), NULL);
    while (state.current_token && state.status > 0)
    {
        process_one_token_for_pipeline(&state);
        if (state.current_token && state.status > 0) // Advance if not done by handler
            state.current_token = state.current_token->next;
    }
    if (state.status > 0 && state.current_exec_node) // Finalize last command group
    {
        if (!finalize_node_group_from_list(state.current_exec_node,
                &(state.current_args_list)))
            state.status = 0;
    }
    if (state.status <= 0) // Malloc or syntax error occurred
    {
        ft_lstclear(&(state.current_args_list), free); // Ensure temp list is cleared
        return (free_exec_list(state.pipeline_head), NULL);
    }
    return (state.pipeline_head);
}

// #include "../../includes/exec.h"

// static t_exec	*new_exec_node(void)
// {
// 	t_exec	*node;

// 	node = malloc(sizeof(t_exec));
// 	if (!node)
// 		return (NULL);
// 	node->group = NULL;
// 	node->infile_name = NULL;
// 	node->outfile_name = NULL;
// 	node->append = 0;
// 	node->heredoc = 0;
// 	node->next = NULL;
// 	return (node);
// }

// static int	is_token(const char *tok, const char *s)
// {
// 	return (ft_strcmp(tok, s) == 0);
// }

// static int	finalize_group_node(t_exec *node, char **cmds, int ncmd)
// {
// 	int	i;

// 	node->group = ft_calloc(ncmd + 1, sizeof(char *));
// 	if (!node->group)
// 		return (-1);
// 	for (i = 0; i < ncmd; ++i)
// 		node->group[i] = ft_strdup(cmds[i]);
// 	node->group[ncmd] = NULL;
// 	return (0);
// }

// t_exec	*split_pipeline_groups(char **tokens)
// {
// 	int		count;
// 	int		i;
// 	t_exec	*head;
// 	t_exec	*current;
// 	char	**cmds;
// 	int		ncmd;

// 	count = 0;
// 	head = NULL;
// 	current = NULL;
// 	ncmd = 0;
// 	while (tokens[count])
// 		count++;
// 	if (count == 0)
// 		return (NULL);
// 	cmds = ft_calloc(count + 1, sizeof(char *));
// 	if (!cmds)
// 		return (NULL);
// 	head = new_exec_node();
// 	if (!head)
// 		return (free(cmds), NULL);
// 	current = head;
// 	i = 0;
// 	while (i < count)
// 	{
// 		if ((is_token(tokens[i], "<") || is_token(tokens[i], "<<")) && i// + 1 < count)
// 		{
// 			if (is_token(tokens[i], "<<"))
// 				current->heredoc = 1;
// 			current->infile_name = tokens[i + 1];
// 			// open_infile_exec(current, current->infile_name);
// 			i += 2;
// 		}
// 		else if ((is_token(tokens[i], ">") || is_token(tokens[i], ">>")) && i
// 			+ 1 < count)
// 		{
// 			current->outfile_name = tokens[i + 1];
// 			if (is_token(tokens[i], ">>"))
// 			current->append = 1;
// 			// open_outfile_exec(current, current->outfile_name, 0);
// 			i += 2;
// 			if (!(i < count && is_token(tokens[i], ">") || is_token(tokens[i],// ">>")))
// 			{
// 				if (finalize_group_node(current, cmds, ncmd) < 0)
// 					break ;
// 				current->next = new_exec_node();
// 				if (!current->next)
// 					break ;
// 				current = current->next;
// 				ncmd = 0;
// 			}
// 		}
// 		else if (is_token(tokens[i], "|"))
// 		{
// 			i++;
// 		}
// 		else
// 		{
// 			cmds[ncmd++] = tokens[i];
// 			i++;
// 		}
// 	}
// 	if (ncmd > 0)
// 		finalize_group_node(current, cmds, ncmd);
// 	free(cmds);
// 	return (head);
// }

#include "../../includes/parsing.h" // For t_token, t_exec, sb_*, etc.
#include "../../includes/struct.h"  // For t_exec definition

static t_exec	*create_new_exec_node(t_exec *previous_node)
{
	t_exec	*node;

	node = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!node)
		return (NULL);
	node->prev = previous_node;
	return (node);
}

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

static int	add_argument_to_temp_list(t_list **temp_args, const char *arg_value)
{
	char	*value_copy;
	t_list	*new_link;

	value_copy = ft_strdup(arg_value);
	if (!value_copy)
		return (0); 
	new_link = ft_lstnew(value_copy);
	if (!new_link)
	{
		free(value_copy);
		return (0);
	}
	ft_lstadd_back(temp_args, new_link);
	return (1);
}

static int	finalize_node_arguments(t_exec *node, t_list **temp_args_ptr)
{
	int		arg_count;
	t_list	*current_link;
	int		i;

	if (!node || !temp_args_ptr)
		return (0); 
	arg_count = ft_lstsize(*temp_args_ptr);
	node->group = (char **)ft_calloc(arg_count + 1, sizeof(char *));
	if (!node->group)
	{
		ft_lstclear(temp_args_ptr, free);
		return (0);
	}
	current_link = *temp_args_ptr;
	i = 0;
	while (current_link)
	{
		node->group[i++] = (char *)current_link->content;
		current_link->content = NULL;
		current_link = current_link->next;
	}
	ft_lstclear(temp_args_ptr, free);
	*temp_args_ptr = NULL;
	return (1);
}

static int	assign_redirection_filename(char **filename_field,
		const char *source_value)
{
	char	*value_copy;

	value_copy = ft_strdup(source_value);
	if (!value_copy)
		return (0);
	free(*filename_field);
	*filename_field = value_copy;
	return (1);
}

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
		return (-1);
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
	*current_token_node_ptr = filename_token;
	return (is_successful ? 1 : 0);
}

static void	initialize_builder_state(t_exec_list_builder_state *state,
		t_token *tokens)
{
	state->current_token = tokens;
	state->list_head = NULL;
	state->current_exec_node = NULL;
	state->temp_arg_list = NULL;
	state->build_status = 1;
	if (tokens)
	{
		state->current_exec_node = create_new_exec_node(NULL);
		if (!state->current_exec_node)
			state->build_status = 0;
		else
			append_exec_node(&state->list_head, &state->current_exec_node,
				state->current_exec_node);
	}
}


static void	process_pipe_token(t_exec_list_builder_state *state)
{
	t_exec	*new_node;

	if (!state->current_exec_node)
	{
		state->build_status = (state->build_status == 1 ?
				-1 : state->build_status);
		return ;
	}
	if (!finalize_node_arguments(state->current_exec_node,
			&state->temp_arg_list))
	{
		state->build_status = 0;
		return ;
	}
	new_node = create_new_exec_node(state->current_exec_node);
	if (!new_node)
	{
		state->build_status = 0;
		return ;
	}
	append_exec_node(&state->list_head, &state->current_exec_node, new_node);
}

static void	process_token_for_list(t_exec_list_builder_state *state)
{
	t_token_type	type;

	if (!state->current_exec_node && state->current_token)
	{
		state->build_status = 0;
		return ;
	}
	type = state->current_token->type;
	if (type == T_WORD)
	{
		if (!add_argument_to_temp_list(&state->temp_arg_list,
				state->current_token->value))
			state->build_status = 0;
	}
	else if (type >= T_REDIRECT_IN && type <= T_HEREDOC)
	{
		state->build_status = handle_node_redirection(state->current_exec_node,
														&state->current_token);
	}
	else if (type == T_PIPE)
		process_pipe_token(state);
}

t_exec	*parse_tokens_to_exec_list(t_token *expanded_tokens)
{
	t_exec_list_builder_state state;

	initialize_builder_state(&state, expanded_tokens);
	if (state.build_status == 0 && expanded_tokens)    
		return (free_exec_list(state.list_head), NULL);
	if (!expanded_tokens)
		return (NULL);
	while (state.current_token && state.build_status > 0)
	{
		process_token_for_list(&state);
		if (state.current_token && state.build_status > 0)
		{
			state.current_token = state.current_token->next;
		}
	}
	if (state.build_status > 0 && state.current_exec_node)
	{
		if (!finalize_node_arguments(state.current_exec_node,
				&state.temp_arg_list))
			state.build_status = 0;
	}
	if (state.build_status <= 0)
	{
		ft_lstclear(&state.temp_arg_list, free);
		return (free_exec_list(state.list_head), NULL);
	}
	return (state.list_head);
}

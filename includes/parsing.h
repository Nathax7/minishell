/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:32:35 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/12 19:00:08 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "signals.h"
# include "utils.h"

t_token			*lexer(const char *line);
int				has_content(const char *line);

int				is_word_char(char c);
int				is_operator_start(char c);

int				create_and_append_token(t_token **head, char *value,
					t_token_type type, t_quote quote_status);
void			free_token_list(t_token *list);

int				handle_pipe_operator(const char **line, t_token **head);
int				handle_lesser_operator(const char **line, t_token **head);
int				handle_greater_operator(const char **line, t_token **head);

int				extract_unquoted_content(const char **line, t_str_builder *sb);
int				extract_quoted_content(const char **line, char quote,
					t_str_builder *sb);
int				has_unclosed_quotes(const char *line);

t_syntax_result	analyze_syntax(t_token *tokens);

t_parse_result	handle_lexer_failure(char **line, char ***accumulated_input);
t_parse_result	handle_syntax_success(char **line, char ***accumulated_input,
					t_syntax_result *result, char **envp, int exit_status,
					t_token **tokens_out);
t_parse_result	handle_syntax_error_case(char **line, char ***accumulated_input,
					t_syntax_result *result);
char			*get_continuation_prompt(t_prompt_type type);

t_token			*expand_tokens(t_token *tokens, char **envp, int exit_status);

char			*expand_variables_in_str(const char *input_str,
					t_quote quote_type, char **envp, int last_exit_status);
char			*get_env_var_value(const char *var_name, char **envp,
					int last_exit_status);
int				is_valid_var_char(char c);

char			**perform_field_splitting(const char *str, const char *sep_val);

int				handle_glob_matches(char **glob_matches, t_token **head,
					char **fields);

t_token			*process_complete_syntax(t_syntax_result syntax_result,
					char **envp, int exit_status);
void			handle_syntax_error(t_syntax_result *result);
t_token			*free_token_list_and_return_null(t_token *list);
char			*cleanup_and_return_char(char *to_free, int to_close,
					char *to_free_optional, int option_flag);

t_token			*parse_complete_input(char **accumulated_input, char **envp,
					int exit_status);
#endif
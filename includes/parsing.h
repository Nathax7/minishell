/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:32:35 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/02 14:49:34 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"

void			sb_init(t_str_builder *sb);
int				sb_append_char(t_str_builder *sb, char c);
int				sb_append_str(t_str_builder *sb, const char *s);
char			*sb_to_string(t_str_builder *sb);
char			*sb_to_string_and_free(t_str_builder *sb);
char			*sb_free_and_return_null(t_str_builder *sb);
int				sb_free_and_return_zero(t_str_builder *sb);
void			sb_free(t_str_builder *sb);

t_token			*lexer(const char *line);
int				has_content(const char *line);

int				is_whitespace(char c);
int				is_word_char(char c);
int				is_operator_start(char c);

t_token			*safe_create_token(char *value, t_token_type type,
					t_quote quote);
int				create_and_append_token(t_token **head, char *value,
					t_token_type type, t_quote quote_status);
void			free_token_list(t_token *list);
int				cleanup_and_return_zero(t_token **head);

int				handle_pipe_operator(const char **line, t_token **head);
int				handle_lesser_operator(const char **line, t_token **head);
int				handle_greater_operator(const char **line, t_token **head);

int				extract_unquoted_content(const char **line, t_str_builder *sb);
int				extract_quoted_content(const char **line, char quote,
					t_str_builder *sb);
int				has_unclosed_quotes(const char *line);
int				handle_quote_continuation(char **line);

t_syntax_result	analyze_syntax(t_token *tokens);

t_token			*handle_syntax_success(char **line, char ***accumulated_input,
					t_syntax_result *result, char **envp, int exit_status);
t_token			*process_complete_syntax(t_syntax_result syntax_result,
					char **envp, int exit_status);
t_token			*parse_complete_input(char **accumulated_input, char **envp,
					int exit_statcount_env_varsus);
char			*get_continuation_prompt(t_prompt_type type);
char			*accumulate_input(char *existing, char *new_input);

int				handle_incomplete_input(char **line,
					t_syntax_result *syntax_result);

t_token			*expand_tokens(t_token *tokens, char **envp, int exit_status);

char			*expand_variables_in_str(const char *input_str,
					t_quote quote_type, char **envp, int last_exit_status);
char			*get_env_var_value(const char *var_name, char **envp,
					int last_exit_status);
int				is_valid_var_char(char c);

char			**perform_field_splitting(const char *str, const char *ifs_val);

int				handle_glob_matches(char **glob_matches, t_token **head,
					char **fields);

char			*process_heredoc(t_token *delimiter, char **envp,
					int exit_status);

void			display_error(const char *context, const char *msg,
					int print_perror);
void			report_syntax_error(const char *near_token);
void			report_syntax_error_detail(const char *message,
					const char *detail);
void			handle_syntax_error(t_syntax_result *result);

void			cleanup_syntax_result(t_syntax_result *result);
void			cleanup_parsing_context(char **line, t_token **tokens,
					t_syntax_result *result);
int				safe_cleanup_and_return_null(char **line, t_token **tokens,
					t_syntax_result *result, char ***accumulated_input);
char			*safe_strdup_or_cleanup(const char *src, char **line,
					t_token **tokens);

char			*secure_readline(const char *prompt);
void			free_char_array(char **array);
char			**safe_realloc_string_array(char **old_array, size_t new_size);

t_token			*handle_quote_incomplete(char **line,
					char ***accumulated_input);
t_token			*handle_lexer_failure(char **line, char ***accumulated_input);
t_token *handle_syntax_error_case(char **line,
	char ***accumulated_input, t_syntax_result *result);
t_token			*handle_incomplete_case(char **line, char ***accumulated_input,
					t_syntax_result *result, t_token *tokens);
t_token			*free_token_list_and_return_null(t_token *list);

void			init_parser_context(t_parser_context *ctx, t_token *tokens,
					t_syntax_result *result);
void			set_syntax_error(t_parser_context *ctx, const char *token_val);
void			set_incomplete_status(t_parser_context *ctx,
					t_parse_status status, t_prompt_type prompt);
int				count_string_array(char **array);

#endif
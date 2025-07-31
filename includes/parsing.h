/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:32:35 by nagaudey          #+#    #+#             */
/*   Updated: 2025/07/31 13:38:57 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "signals.h"
# include "utils.h"

t_token			*lexer(const char *line);
int				has_content(const char *line);
int				handle_pipe_operator(const char **line, t_token **head);
int				handle_lesser_operator(const char **line, t_token **head);
int				handle_greater_operator(const char **line, t_token **head);
int				extract_unquoted_content(const char **line, t_str_builder *sb);
int				extract_quoted_content(const char **line, char quote,
					t_str_builder *sb);
int				has_unclosed_quotes(const char *line);
t_syntax_result	analyze_syntax(t_token *tokens);
t_parse_result	handle_syntax_success(t_syntax_result *result, char **envp,
					int exit_status);
t_syntax_result	analyze_syntax(t_token *tokens);
t_token			*expand_tokens(t_token *tokens, char **envp, int exit_status);
char			*expand_variables_in_str(const char *input_str, char **envp, int last_exit_status);
int				should_expand_variable(char current_char, char next_char,
					t_quote quote_type);
int				is_valid_var_char(char c);
char			**perform_field_splitting(const char *str, const char *sep_val);
t_token			*process_complete_syntax(t_syntax_result syntax_result,
					char **envp, int exit_status);
void			handle_syntax_error(t_syntax_result *result);
t_token			*free_token_list_and_return_null(t_token *list);
t_token			*parse_complete_input(char *line, char **envp,
					int *exit_status);
void			free_token_list(t_token *list);
int				process_expansion(t_str_builder *sb, const char **ip,
					char **envp, int last_exit_status);
int				process_word_expansion(t_token *token, t_token **expanded_head,
					char **envp, int exit_status);
char			*expand_token_value(const char *value, t_quote quote_type,
					char **envp, int exit_status);
int				should_field_split(t_quote quote_type);
int				process_word(const char **line, t_token **head);
int				process_heredoc_word(t_token *current, t_token **expanded_head);
int				process_regular_word(t_token *current, t_token **expanded_head,
					t_expand_context *ctx);
int				process_word_token(t_token *current, t_token *prev,
					t_token **expanded_head, t_expand_context *ctx);
int				process_non_word_token(t_token *current,
					t_token **expanded_head);
int				process_single_token(t_token *current, t_token *prev,
					t_token **expanded_head, t_expand_context *ctx);

#endif
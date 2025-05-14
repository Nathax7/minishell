/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:32:35 by nagaudey          #+#    #+#             */
/*   Updated: 2025/05/12 20:53:58 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "utils.h"

// string builder
void	sb_init(t_str_builder *sb);
int		sb_append_char(t_str_builder *sb, char c);
int		sb_append_str(t_str_builder *sb, const char *s);
char	*sb_to_string(t_str_builder *sb);
void	sb_free(t_str_builder *sb);

// lexer utilities
void	free_token_list(t_token *list);
int	create_and_append_token(t_token **head, char *value, t_token_type type,
	t_quote quote_status, t_word_segment *segments);
int		is_whitespace(char c);
int		is_word_char(char c);
int		is_operator_start(char c);
void	append_segment(t_word_segment **head, t_word_segment *new_segment);
t_word_segment	*create_word_segment(char *value, t_quote quote_type);

// lexer functions
t_token	*lexer(const char *line);

// token conversion to array functions
char	**convert_token_list_to_char_array(t_token *token_list);
void	free_char_array(char **array);

// error management functions
void	display_error(const char *context, const char *msg, int print_perror);
void	report_syntax_error(const char *near_token);
void	report_syntax_error_detail(const char *message, const char *detail);

// expander utils
char	*get_env_var_value(const char *var_name, char **envp,
			int last_exit_status);
int		is_valid_var_char(char c);

// variable expansion
char	*expand_variables_in_str(const char *input_str, t_quote quote_type,
			char **envp, int last_exit_status);

// expander
t_token	*perform_all_expansions(t_token *raw_list_head, char **envp,
			int current_exit_status);

extern int g_exit_status;

#endif
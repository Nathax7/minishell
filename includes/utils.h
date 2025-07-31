/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:20:40 by almeekel          #+#    #+#             */
/*   Updated: 2025/07/31 16:41:45 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	cleanup_child_resources(t_exec *exec);
void	free_child(t_exec *exec, int status, char *str1, char *str2);
void	free_parent(t_exec *exec, int status, char *str1, char *str2);
void	ft_message(char *command, char *arg, char *error);
void	free_split(char **arr);
int		find_size(t_token *lst);
void	free_split(char **arr);
t_cmd	*find_last_cmd(t_cmd *lst);
t_args	*find_last_args(t_args *lst);
t_files	*find_last_files(t_files *lst);
t_cmd	*find_first_cmd(t_cmd *lst);
t_args	*find_first_args(t_args *lst);
t_files	*find_first_files(t_files *lst);
int		find_size(t_token *lst);
int		find_size_cmd(t_cmd *lst);
int		find_size_args(t_args *lst);
char	*ft_strjoin_space(char const *s1, char const *s2);
void	create_pipes(t_exec *exec);
void	close_all_pipes(t_exec *exec);
void	close_child_fds(t_exec *exec);
void	free_cmd_list(t_cmd *cmd_list, int is_parent);
void	free_args_list(t_args *args);
void	free_files_list(t_files *files);
void	cleanup_cmd_list(t_exec *exec, int parent);
int		unlink_heredoc(t_files *files);
void	free_token(t_token *token, int status, char *str, char *str2);
char	*get_env_var_value(const char *var_name, char **envp,
			int *last_exit_status);
int		is_valid_var_char(char c);
void	sb_init(t_str_builder *sb);
int		sb_append_char(t_str_builder *sb, char c);
int		sb_append_str(t_str_builder *sb, const char *s);
char	*sb_to_string(t_str_builder *sb);
char	*sb_to_string_and_free(t_str_builder *sb);
char	*sb_free_and_return_null(t_str_builder *sb);
int		sb_free_and_return_zero(t_str_builder *sb);
void	sb_free(t_str_builder *sb);
char	*create_env_string(char *name, char *value);
int		count_env_vars(char **envp);
char	*find_env_var(char **envp, const char *name);
int		find_env_index(char **envp, const char *name);
char	**copy_env_array(char **envp);
char	**copy_basic_env(char **envp);
int		add_missing_pwd(char ***env_ptr);
int		add_missing_shlvl(char ***env_ptr);
int		add_missing_underscore(char ***env_ptr);
void	*cleanup_parsing_and_return_null(t_syntax_result *result,
			char *error_msg);
void	report_syntax_error(char *near_token);
void	handle_syntax_error(t_syntax_result *result);
int		create_and_append_token(t_token **head, char *value1);
int		is_word_char(char c);
int		is_operator_start(char c);
void	free_token_list(t_token *list);
char	*find_env_value(char **envp, const char *name);
int		set_env_var(char ***env_ptr, char *name, char *value);
void	safe_close(int *fd);
char	*expand_heredoc_line(const char *line, char **envp);
void	free_pipes(t_exec *exec, int failed_index);
t_cmd	*free_parsing_cmd(t_cmd **head);
int		ft_return_message(char *command, char *arg, char *error, int status);
int		free_infile_name(t_files *files);
void	dup_and_close(int *fd, int std);
void	remove_env_variable(char ***env_ptr, const char *name);

int		handle_quote_start(t_str_builder *sb, const char **ip,
			char *current_quote);
int		handle_quote_end(t_str_builder *sb, const char **ip,
			char *current_quote);
int		handle_single_quote(t_str_builder *sb, const char **ip);
int		handle_double_quote_escape(t_str_builder *sb, const char **ip);
void	free_exit(t_exec *exec, int parent, int status);
void	print_str_builder(const t_str_builder *sb);
void	print_token_list(const t_token *head);
char	*remove_outer_quotes(const char *str);
void	print_escaped_value(const char *value);


#endif
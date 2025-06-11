/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:07:53 by nagaudey          #+#    #+#             */
/*   Updated: 2025/06/11 16:20:42 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	ft_message(char *str, char *str2);
int		usage(void);
void	free_split(char **arr);
void	free_triple(char ***triple);
int		find_size(t_token *lst);

// structs
char	**safe_realloc_string_array(char **old_array, size_t new_size);

// t_exec management 1!!!
t_exec	*find_last(t_exec *lst);
t_exec	*find_first(t_exec *lst);
void	open_infile(t_exec *exec, char *infile);
void	open_outfile(t_exec *exec, char *outfile, int mode);
void	free_token(t_token *token, int status, char *str, char *str2);
void	free_pipex(t_exec *exec, int status, char *str, char *str2);
void	free_pipex_core(t_exec *exec);
void	ft_close(t_exec *exec, t_type type);
void	free_exec(t_exec *exec, int status, char *str, char *str2);
void	open_infile(t_exec *exec, char *infile);
int		open_infile_exec(t_exec *exec, char *infile);
void	open_outfile(t_exec *exec, char *outfile, int mode);
int		open_outfile_exec(t_exec *exec, char *outfile, int mode);
void	free_exec_core(t_exec *node);

// t_token
char	**safe_realloc_string_array(char **old_array, size_t new_size);
int		count_string_array(char **array);

// t_context

// expanding utils
char	*get_env_var_value(const char *var_name, char **envp,
			int last_exit_status);
int		is_valid_var_char(char c);

// error management utils
void	handle_syntax_error(t_syntax_result *result);
void	report_syntax_error(const char *near_token);

// clean string building util
void	sb_init(t_str_builder *sb);
int		sb_append_char(t_str_builder *sb, char c);
int		sb_append_str(t_str_builder *sb, const char *s);
char	*sb_to_string(t_str_builder *sb);
char	*sb_to_string_and_free(t_str_builder *sb);
char	*sb_free_and_return_null(t_str_builder *sb);
int		sb_free_and_return_zero(t_str_builder *sb);
void	sb_free(t_str_builder *sb);

// builtin_utils
char	*create_env_string(const char *name, const char *value);
int		count_env_vars(char **envp);
char	*find_env_var(char **envp, const char *name);
int		find_env_index(char **envp, const char *name);
char	**copy_env_array(char **envp);
int		set_env_var(char ***env_ptr, char *name, char *value);
char	*get_env_var_value(const char *var_name, char **envp,
			int last_exit_status);
int		is_valid_var_char(char c);

#endif